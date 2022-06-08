// Copyright (c) 2015-2017, The Bytecoin developers
// Copyright (c) 2017-2022, The Karbo developers
//
// This file is part of Karbovanets.
//
// Karbovanets is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Karbovanets is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Karbovanets.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <thread>
#include <future>

#include <QMessageBox>
#include <QEventLoop>
#include <QThread>
#include <QTimerEvent>
#include <QUrl>
#include <QVersionNumber>

#include "CryptoNoteAdapter.h"
#include "WalletLogger/WalletLogger.h"
#include "IBlockChainExplorerAdapter.h"
//#include "InProcessNodeAdapter.h"
#include "ProxyRpcNodeAdapter.h"
#include "Settings/Settings.h"
#include "Rpc/CoreRpcServerCommandsDefinitions.h"
#include "Rpc/HttpClient.h"
#include "CryptoNoteProtocol/CryptoNoteProtocolHandler.h"

#include "CryptoNoteCore/TransactionExtra.h"

#include "version.h"

namespace WalletGui {

namespace {

const int AUTO_CONNECTION_INTERVAL = 200;
const char OLD_CORE_LOG_FILE_NAME[] = "karbowallet.log";

}

CryptoNoteAdapter::CryptoNoteAdapter(const QDir& _dataDir, bool _testnet, bool _debug, QObject* _parent) : QObject(_parent),
  m_dataDir(_dataDir), m_testnet(_testnet), m_debug(_debug), m_connectionMethod(ConnectionMethod::REMOTE),
  m_localDaemodPort(CryptoNote::RPC_DEFAULT_PORT), m_remoteDaemonUrl(), m_coreLogger(), m_walletLogger(),
  m_currency(CryptoNote::CurrencyBuilder(m_coreLogger).currency()),
  m_nodeAdapter(nullptr), m_autoConnectionTimerId(-1),
  m_dispatcher() {
}

CryptoNoteAdapter::~CryptoNoteAdapter() {
}

inline std::string interpret_rpc_response(bool ok, const std::string& status) {
  std::string err;
  if (ok) {
    if (status == CORE_RPC_STATUS_BUSY) {
      err = "daemon is busy. Please try later";
    } else if (status != CORE_RPC_STATUS_OK) {
      err = status;
    }
  } else {
    err = "possible lost connection to daemon";
  }
  return err;
}

int CryptoNoteAdapter::init(ConnectionMethod _connectionMethod, quint16 _localDaemonPort,
  const QUrl& _remoteDaemonUrl) {
  WalletLogger::debug(tr("[CryptoNote wrapper] Initializing..."));
  Q_ASSERT(m_nodeAdapter == nullptr);
  m_connectionMethod = _connectionMethod;
  m_localDaemodPort = _localDaemonPort;
  m_remoteDaemonUrl = _remoteDaemonUrl;
  QEventLoop initLoop;
  bool initCompleted = false;
  QMetaObject::Connection connection = connect(this, &CryptoNoteAdapter::initCompletedSignal, [&initLoop, &initCompleted](int _initStatus) {
    initCompleted = true;
    initLoop.exit(_initStatus);
  });

  initCoreLogger(m_debug);
  initWalletLogger(m_debug);
  initNode();
  int initStatus = initLoop.exec();
  if (!initCompleted) {
    initStatus = -1;
  }

  disconnect(connection);

  WalletLogger::debug(tr("[CryptoNote wrapper] Init status: %1").arg(initStatus));
  return initStatus;
}

void CryptoNoteAdapter::deinit() {
  WalletLogger::debug(tr("[CryptoNote wrapper] Deinitializing..."));
  Q_ASSERT(m_nodeAdapter != nullptr);
  /*if (m_nodeAdapter->getBlockChainExplorerAdapter() != nullptr) {
    m_nodeAdapter->getBlockChainExplorerAdapter()->deinit();
  }*/

  m_nodeAdapter->deinit();
  dynamic_cast<QObject*>(m_nodeAdapter)->deleteLater();
  m_nodeAdapter = nullptr;
  Q_EMIT deinitCompletedSignal();
}

INodeAdapter* CryptoNoteAdapter::getNodeAdapter() const {
  //Q_ASSERT(m_nodeAdapter != nullptr);
  return m_nodeAdapter;
}

bool CryptoNoteAdapter::isValidAddress(const QString& _address) const {
  CryptoNote::AccountPublicAddress internalAddress;
  return m_currency.parseAccountAddressString(_address.toStdString(), internalAddress);
}

bool CryptoNoteAdapter::isValidPaymentId(const QString& _paymentId) const {
  if (_paymentId.length() != 2 * sizeof(Crypto::Hash)) {
    return false;
  }

  QByteArray byteArray = QByteArray::fromHex(_paymentId.toUtf8());
  return byteArray.size() == sizeof(Crypto::Hash);
}

QString CryptoNoteAdapter::getCurrencyTicker() const {
  return "KRB";
}

quint64 CryptoNoteAdapter::getMinimalFee() const {
  return m_currency.minimumFee();
}

quint64 CryptoNoteAdapter::getTargetTime() const {
  return m_currency.difficultyTarget();
}

QString CryptoNoteAdapter::formatAmount(qint64 _amount) const {
  QString result = QString::number(qAbs(_amount));
  quintptr numberOfDecimalPlaces = m_currency.numberOfDecimalPlaces();
  if (result.length() < numberOfDecimalPlaces + 1) {
    result = result.rightJustified(numberOfDecimalPlaces + 1, '0');
  }

  quint32 dotPos = result.length() - numberOfDecimalPlaces;
  for (quint32 pos = result.length() - 1; pos > dotPos + 1; --pos) {
    if (result[pos] == '0') {
      result.remove(pos, 1);
    } else {
      break;
    }
  }

  result.insert(dotPos, ".");
  for (qint32 pos = dotPos - 3; pos > 0; pos -= 3) {
    if (result[pos - 1].isDigit()) {
      //result.insert(pos, ',');
    }
  }

  return _amount < 0 ? result.prepend("-") : result;
}

QString CryptoNoteAdapter::formatUnsignedAmount(quint64 _amount) const {
  QString result = QString::number(_amount);
  quintptr numberOfDecimalPlaces = m_currency.numberOfDecimalPlaces();
  if (result.length() < numberOfDecimalPlaces + 1) {
    result = result.rightJustified(numberOfDecimalPlaces + 1, '0');
  }

  quint32 dotPos = result.length() - numberOfDecimalPlaces;
  for (quint32 pos = result.length() - 1; pos > dotPos + 1; --pos) {
    if (result[pos] == '0') {
      result.remove(pos, 1);
    } else {
      break;
    }
  }

  result.insert(dotPos, ".");
  for (qint32 pos = dotPos - 3; pos > 0; pos -= 3) {
    if (result[pos - 1].isDigit()) {
      //result.insert(pos, ',');
    }
  }

  return result;
}

QString CryptoNoteAdapter::formatAmountToShort(qint64 _amount) const {
  QString amountString = formatAmount(_amount);
  int dotPos = amountString.indexOf('.');
  if (amountString.length() - dotPos <= 5) {
    return amountString;
  }

  QString result = amountString.left(dotPos + 1);
  for (int i = dotPos + 1; i < dotPos + 5; ++i) {
    result.append(amountString[i]);
  }

  return result;
}

qint64 CryptoNoteAdapter::parseAmount(const QString& _amountString) const {
  QString amountString = _amountString.trimmed().remove(',');
  bool negative = amountString.startsWith('-');
  if (negative) {
    amountString.remove(0, 1);
  }

  uint64_t amount;
  if (!m_currency.parseAmount(amountString.toStdString(), amount)) {
    amount = 0;
  }

  return negative ? -static_cast<qint64>(amount) : static_cast<qint64>(amount);
}

quint64 CryptoNoteAdapter::parseUnsignedAmount(const QString& _amountString) const {
  QString amountString = _amountString.trimmed().remove(',');
  uint64_t amount;
  if (!m_currency.parseAmount(amountString.toStdString(), amount)) {
    amount = 0;
  }

  return amount;
}

std::string CryptoNoteAdapter::convertPaymentToExtra(const QString& _paymentIdString) const {
  if (_paymentIdString.isEmpty()) {
    return "";
  }

  std::string paymentIdString = _paymentIdString.toStdString();

  Crypto::Hash paymentId;
  if (!CryptoNote::parsePaymentId(paymentIdString, paymentId)) {
    return "";
  }

  std::vector<uint8_t> extra;
  CryptoNote::BinaryArray extraNonce;
  CryptoNote::setPaymentIdToTransactionExtraNonce(extraNonce, paymentId);
  if (!CryptoNote::addExtraNonceToTransactionExtra(extra, extraNonce)) {
    return "";
  }

  return std::string(extra.begin(), extra.end());
}

QString CryptoNoteAdapter::extractPaymentIdFromExtra(const std::string& _extra) const {
  std::vector<CryptoNote::TransactionExtraField> extraFields;
  std::vector<uint8_t> extraVector;
  std::copy(_extra.begin(), _extra.end(), std::back_inserter(extraVector));

  if (!CryptoNote::parseTransactionExtra(extraVector, extraFields)) {
    return QString();
  }

  CryptoNote::TransactionExtraNonce extraNonce;
  if (CryptoNote::findTransactionExtraFieldByType(extraFields, extraNonce)) {
    Crypto::Hash paymentIdHash;
    if (CryptoNote::getPaymentIdFromTransactionExtraNonce(extraNonce.nonce, paymentIdHash)) {
      return QByteArray(reinterpret_cast<char*>(&paymentIdHash), sizeof(paymentIdHash)).toHex();
    }
  }

  return QByteArray();
}

bool CryptoNoteAdapter::parseAccountAddressString(QString& _address, CryptoNote::AccountPublicAddress& _internalAddress) {
  return m_currency.parseAccountAddressString(_address.toStdString(), _internalAddress);
}

void CryptoNoteAdapter::addObserver(ICryptoNoteAdapterObserver* _observer) {
  QObject* observer = dynamic_cast<QObject*>(_observer);
  connect(this, SIGNAL(initCompletedSignal(int)), observer, SLOT(cryptoNoteAdapterInitCompleted(int)));
  connect(this, SIGNAL(deinitCompletedSignal()), observer, SLOT(cryptoNoteAdapterDeinitCompleted()));
}

void CryptoNoteAdapter::removeObserver(ICryptoNoteAdapterObserver* _observer) {
  QObject* observer = dynamic_cast<QObject*>(_observer);
  disconnect(this, SIGNAL(initCompletedSignal(int)), observer, SLOT(cryptoNoteAdapterInitCompleted(int)));
  disconnect(this, SIGNAL(deinitCompletedSignal()), observer, SLOT(cryptoNoteAdapterDeinitCompleted()));
}

void CryptoNoteAdapter::initCompleted(int _status) {
  if (_status == INodeAdapter::INIT_SUCCESS && m_nodeAdapter->getBlockChainExplorerAdapter() != nullptr) {
    m_nodeAdapter->getBlockChainExplorerAdapter()->init();
  }

  if (m_nodeAdapter->getNodeType() == NodeType::IN_PROCESS || m_autoConnectionTimerId == -1) {
    m_nodeAdapter->removeObserver(this);
    Q_EMIT initCompletedSignal(_status);
  }
}

void CryptoNoteAdapter::deinitCompleted() {
  // Do nothing
}

void CryptoNoteAdapter::peerCountUpdated(quintptr _count) {
  if (m_nodeAdapter->getNodeType() == NodeType::RPC && m_autoConnectionTimerId != -1) {
    killTimer(m_autoConnectionTimerId);
    m_autoConnectionTimerId = -1;
    m_nodeAdapter->removeObserver(this);
    Q_EMIT initCompletedSignal(INodeAdapter::INIT_SUCCESS);
  }
}

void CryptoNoteAdapter::localBlockchainUpdated(CryptoNote::BlockHeaderInfo _lastLocalBlockInfo) {
  if (m_nodeAdapter->getNodeType() == NodeType::RPC && m_autoConnectionTimerId != -1) {
    killTimer(m_autoConnectionTimerId);
    m_autoConnectionTimerId = -1;
    m_nodeAdapter->removeObserver(this);
    Q_EMIT initCompletedSignal(INodeAdapter::INIT_SUCCESS);
  }
}

void CryptoNoteAdapter::lastKnownBlockHeightUpdated(quint32 _height) {
  if (m_nodeAdapter->getNodeType() == NodeType::RPC && m_autoConnectionTimerId != -1) {
    killTimer(m_autoConnectionTimerId);
    m_autoConnectionTimerId = -1;
    m_nodeAdapter->removeObserver(this);
    Q_EMIT initCompletedSignal(INodeAdapter::INIT_SUCCESS);
  }
}

void CryptoNoteAdapter::connectionStatusUpdated(bool _connected) {
  WalletLogger::debug(tr("[CryptoNote wrapper] Connection status updated: %1").arg(_connected));
  if (m_nodeAdapter->getNodeType() == NodeType::RPC && m_autoConnectionTimerId != -1 && !_connected) {
    onLocalDaemonNotFound();
  }
}

void CryptoNoteAdapter::timerEvent(QTimerEvent* _event) {
  if (_event->timerId() == m_autoConnectionTimerId) {
    WalletLogger::debug(tr("[CryptoNote wrapper] Timeout event"));
    onLocalDaemonNotFound();
    return;
  }

  QObject::timerEvent(_event);
}

void CryptoNoteAdapter::initCoreLogger(bool _debug) {
  if (QFile::exists(m_dataDir.absoluteFilePath(OLD_CORE_LOG_FILE_NAME))) {
    QFile::rename(m_dataDir.absoluteFilePath(OLD_CORE_LOG_FILE_NAME), m_dataDir.absoluteFilePath(CORE_LOG_FILE_NAME));
  }

  configureLogger(m_coreLogger, m_dataDir.absoluteFilePath(CORE_LOG_FILE_NAME), _debug);
}

void CryptoNoteAdapter::initWalletLogger(bool _debug) {
  configureLogger(m_walletLogger, m_dataDir.absoluteFilePath(WALLET_LOG_FILE_NAME), _debug);
}

void CryptoNoteAdapter::initNode() {
  Q_ASSERT(m_nodeAdapter == nullptr);
  QString message = tr("Connecting...");
  Q_EMIT connectingToNodeStatus(message);
  switch(m_connectionMethod) {
  case ConnectionMethod::AUTO:
    initAutoConnection();
    break;
  case ConnectionMethod::EMBEDDED:
    //initInProcessNode();
    break;
  case ConnectionMethod::LOCAL:
    initLocalRpcNode();
    break;
  case ConnectionMethod::REMOTE:
    initRemoteRpcNode();
    break;
  }
}

void CryptoNoteAdapter::initAutoConnection() {
  WalletLogger::info(tr("[CryptoNote wrapper] Auto connection is On"));
  WalletLogger::info(tr("[CryptoNote wrapper] Searching local daemon: 127.0.0.1:%1").arg(CryptoNote::RPC_DEFAULT_PORT));
  QUrl localDaemonUrl = QUrl::fromUserInput("http://127.0.0.1:" + QString::number(CryptoNote::RPC_DEFAULT_PORT));
  if (isNodeAvailable(localDaemonUrl)) {
    m_nodeAdapter = new ProxyRpcNodeAdapter(m_currency, m_coreLogger, m_walletLogger, localDaemonUrl, this);
    m_nodeAdapter->addObserver(this);
    m_autoConnectionTimerId = startTimer(AUTO_CONNECTION_INTERVAL);
    m_nodeAdapter->init();
  } else {
    initRemoteRpcNode();
  }
}

void CryptoNoteAdapter::initLocalRpcNode() {
  WalletLogger::info(tr("[CryptoNote wrapper] Starting with local daemon: 127.0.0.1:%1").arg(CryptoNote::RPC_DEFAULT_PORT));
  m_nodeAdapter = new ProxyRpcNodeAdapter(m_currency, m_coreLogger, m_walletLogger, QUrl::fromUserInput("http://127.0.0.1:" + QString::number(m_localDaemodPort)), this);
  m_nodeAdapter->addObserver(this);
  m_nodeAdapter->init();
}

void CryptoNoteAdapter::initRemoteRpcNode() {
  WalletLogger::info(tr("[CryptoNote wrapper] Starting with remote node: %1:%2").arg(m_remoteDaemonUrl.host()).arg(m_remoteDaemonUrl.port()));

  // check if the node is available first
  if (!isNodeAvailable(m_remoteDaemonUrl)) {
    QString message = tr("Node is not responding...");
    WalletLogger::info(tr("[CryptoNote wrapper] Node %1:%2 is not responding").arg(m_remoteDaemonUrl.host()).arg(m_remoteDaemonUrl.port()));
    Q_EMIT connectingToNodeStatus(message);
    // fallback to auto?
    findNodeAttempts = 0;
    if(getWorkingRandomNode()) {
      initRemoteRpcNode();
    } else {
      WalletLogger::info(tr("[CryptoNote wrapper] Could not connect to any node!!!"));
      initLocalRpcNode(); // fallback
    }
  }

  m_nodeAdapter = new ProxyRpcNodeAdapter(m_currency, m_coreLogger, m_walletLogger, m_remoteDaemonUrl, this);
  m_nodeAdapter->addObserver(this);
  m_nodeAdapter->init();
}

void CryptoNoteAdapter::onLocalDaemonNotFound() {
  killTimer(m_autoConnectionTimerId);
  m_autoConnectionTimerId = -1;
  WalletLogger::info(tr("[CryptoNote wrapper] Local daemon on 127.0.0.1:%1 not found").arg(CryptoNote::RPC_DEFAULT_PORT));
  deinit();
  WalletLogger::info(tr("[CryptoNote wrapper] Trying to connect to remote node..."));
  if (isNodeAvailable(m_remoteDaemonUrl)) { // check if the node is available first
    initRemoteRpcNode();
  } else {
    findNodeAttempts = 0;
    if(getWorkingRandomNode()) {
      initRemoteRpcNode();
    } else {
      WalletLogger::info(tr("[CryptoNote wrapper] Could not connect to any node!!!"));
      initLocalRpcNode(); // fallback
    }
  }
}

void CryptoNoteAdapter::configureLogger(Logging::LoggerManager& _logger, const QString& _logFilePath, bool _debug) {
  Logging::Level level = _debug ? Logging::DEBUGGING : Logging::INFO;
  Common::JsonValue loggerConfiguration(Common::JsonValue::OBJECT);
  loggerConfiguration.insert("globalLevel", static_cast<int64_t>(level));
  Common::JsonValue& cfgLoggers = loggerConfiguration.insert("loggers", Common::JsonValue::ARRAY);
  Common::JsonValue& fileLogger = cfgLoggers.pushBack(Common::JsonValue::OBJECT);
  fileLogger.insert("type", "file");
  fileLogger.insert("filename", std::string(_logFilePath.toLocal8Bit().data()));
  fileLogger.insert("level", static_cast<int64_t>(level));
  _logger.configure(loggerConfiguration);
}

bool CryptoNoteAdapter::getNodeInfo(QUrl _node, CryptoNote::COMMAND_RPC_GET_INFO::response& info) {
  CryptoNote::COMMAND_RPC_GET_INFO::request req;
  CryptoNote::COMMAND_RPC_GET_INFO::response res;
  try {
    CryptoNote::HttpClient httpClient(m_dispatcher, _node.host().toStdString(), _node.port(), _node.scheme().compare("https") == 0);
    CryptoNote::invokeJsonCommand(httpClient, "/getinfo", req, res);
    std::string err = interpret_rpc_response(true, res.status);
    if (err.empty()) {
      info = res;
      return true;
    } else {
      WalletLogger::info(tr("[CryptoNote wrapper] Failed to invoke request: %1").arg(QString::fromStdString(err)));
      return false;
    }
  }
  catch (const CryptoNote::ConnectException&) {
    WalletLogger::info(tr("[CryptoNote wrapper] Failed to connect to node."));
    return false;
  } catch (const std::exception& e) {
    WalletLogger::info(tr("[CryptoNote wrapper] Failed to invoke rpc method: %1").arg(e.what()));
    return false;
  }
}

bool CryptoNoteAdapter::isNodeAvailable(QUrl _node) {
  WalletLogger::info(tr("[CryptoNote wrapper] Checking node: %1:%2 ...").arg(_node.host()).arg(_node.port()));

  QString ourVersionStr = PROJECT_VERSION;
  if (ourVersionStr.startsWith(QStringLiteral("v.")))
      ourVersionStr.remove(0, 2);
  else if (ourVersionStr.startsWith('v'))
      ourVersionStr.remove(0, 1);

  CryptoNote::COMMAND_RPC_GET_INFO::response res;
  bool r = false;

  try {
      auto future = std::async(std::launch::async, [this, &r, &_node, &res]() {

      r = getNodeInfo(_node, res);

      });

      std::future_status status;

      status = future.wait_for(std::chrono::milliseconds(200));

      if (status == std::future_status::timeout) {
        WalletLogger::info(tr("[CryptoNote wrapper] Timeout response from node %1").arg(_node.toString()));
        return false;
      }
      else if (status == std::future_status::ready) {
        future.get();
      }
  }
  catch (std::runtime_error& e) {
    WalletLogger::info(tr("[CryptoNote wrapper] Error connecting to node: %1").arg(QString::fromStdString(e.what())));
    return false;
  }

  if (r) {

    std::string err = interpret_rpc_response(true, res.status);

    // check if node is up-to-date
    WalletLogger::info(tr("[CryptoNote wrapper] Checking remote node %1:%2 version").arg(_node.host()).arg(_node.port()));

    if (err.empty()) {
      QString remoteVersionStr = QString::fromStdString(res.version);
      if (!remoteVersionStr.isEmpty()) {
        remoteVersionStr.remove(5, remoteVersionStr.length());

        int suffixIndex;
        QVersionNumber ourVersion = QVersionNumber::fromString(ourVersionStr, &suffixIndex);
        QVersionNumber remoteVersion = QVersionNumber::fromString(remoteVersionStr, &suffixIndex);

        WalletLogger::debug(tr("[CryptoNote wrapper] needed version %1").arg(ourVersionStr));
        WalletLogger::debug(tr("[CryptoNote wrapper] remote version %1").arg(remoteVersionStr));

        bool r = QVersionNumber::compare(remoteVersion, ourVersion) < 0;
        if (r) {
          WalletLogger::info(tr("[CryptoNote wrapper] Remote node %1:%2 version %3 is outdated.").arg(_node.host()).arg(_node.port()).arg(QString::fromStdString(res.version)));
          //return false;
        }
        else {
          WalletLogger::info(tr("[CryptoNote wrapper] Remote node %1:%2 version %3 is OK").arg(_node.host()).arg(_node.port()).arg(QString::fromStdString(res.version)));
        }
      }

      return true;
    }
  }

  return false;
}

bool CryptoNoteAdapter::getWorkingRandomNode(){
  QUrl random_node = Settings::instance().getRandomNode();
  if(isNodeAvailable(random_node)) {
    m_remoteDaemonUrl = random_node;
    Settings::instance().setRemoteRpcUrl(random_node);
    return true;
  } else {
    if (findNodeAttempts > 10) {
      WalletLogger::info(tr("[CryptoNote wrapper] Failed to find any working node after 10 attempts."));
      return false;
    } else {
      findNodeAttempts++;
      getWorkingRandomNode();
    }
  }
}

}
