// Copyright (c) 2015-2017, The Bytecoin developers
//
// This file is part of Bytecoin.
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

#include <QUrl>
#include <QComboBox>

#include <CryptoNoteConfig.h>

#include "ConnectionOptionsFrame.h"
#include "Settings/Settings.h"
#include "ICryptoNoteAdapter.h"
#include "INodeAdapter.h"
#include "Style/Style.h"

#include "ui_ConnectionOptionsFrame.h"

namespace WalletGui {

namespace {

const char CONNECTION_OPTIONS_STYLE_SHEET_TEMPLATE[] =
  "WalletGui--ConnectionOptionsFrame {"
    "background: #ffffff;"
  "}"

  "WalletGui--ConnectionOptionsFrame QRadioButton {"
    "spacing: 20px;"
  "}"

  "WalletGui--ConnectionOptionsFrame QRadioButton,"
  "WalletGui--ConnectionOptionsFrame QLineEdit,"
  "WalletGui--ConnectionOptionsFrame QSpinBox {"
    "min-height: 25px;"
    "max-height: 25px;"
  "}";

bool isIpOrHostName(const QString& _string) {
  QRegExp ipRegExp("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
  QRegExp hostNameRegExp("^(([a-zA-Z0-9]|[a-zA-Z0-9][a-zA-Z0-9\\-]*[a-zA-Z0-9])\\.)*([A-Za-z0-9]|[A-Za-z0-9][A-Za-z0-9\\-]*[A-Za-z0-9])$");
  return !_string.isEmpty() && (ipRegExp.exactMatch(_string) || hostNameRegExp.exactMatch(_string));
}

}

ConnectionOptionsFrame::ConnectionOptionsFrame(QWidget* _parent) : QFrame(_parent),
  m_ui(new Ui::ConnectionOptionsFrame), m_cryptoNoteAdapter(nullptr), m_nodeModel(new NodeModel(this)) {
  m_ui->setupUi(this);
  m_ui->remoteNodesComboBox->setModel(m_nodeModel);
  m_ui->m_connectionButtonGroup->setId(m_ui->m_autoRadio, static_cast<int>(ConnectionMethod::AUTO));
  m_ui->m_connectionButtonGroup->setId(m_ui->m_localRadio, static_cast<int>(ConnectionMethod::LOCAL));
  m_ui->m_connectionButtonGroup->setId(m_ui->m_remoteRadio, static_cast<int>(ConnectionMethod::REMOTE));
  setStyleSheet(Settings::instance().getCurrentStyle().makeStyleSheet(CONNECTION_OPTIONS_STYLE_SHEET_TEMPLATE));
  m_ui->addNodeButton->setEnabled(false);
}

ConnectionOptionsFrame::~ConnectionOptionsFrame() {
}

void ConnectionOptionsFrame::load() {
  m_ui->m_localPortSpin->setValue(Settings::instance().getLocalRpcPort());
  QUrl remoteUrl = Settings::instance().getRemoteRpcUrl();
  if (!remoteUrl.isEmpty()) {
    int index = m_ui->remoteNodesComboBox->findData(remoteUrl.host());
    if (index != -1) {
       m_ui->remoteNodesComboBox->setCurrentIndex(index);
    }
  }
  switch (Settings::instance().getConnectionMethod()) {
  case ConnectionMethod::AUTO:
    m_ui->m_autoRadio->toggle();
    break;
  case ConnectionMethod::LOCAL:
    m_ui->m_localRadio->toggle();
    break;
  case ConnectionMethod::REMOTE:
    m_ui->m_remoteRadio->toggle();
    break;
  }
  m_ui->removeNodeButton->setEnabled(m_ui->remoteNodesComboBox->count() != 0);
  // remoteHostNameChanged(m_ui->remoteNodesComboBox->currentText().split(":")[0]);
}

void ConnectionOptionsFrame::save() {
  Settings::instance().setConnectionMethod(static_cast<ConnectionMethod>(m_ui->m_connectionButtonGroup->checkedId()));
  Settings::instance().setLocalRpcPort(m_ui->m_localPortSpin->value());
  Settings::instance().setRemoteRpcUrl(QUrl::fromUserInput(m_ui->remoteNodesComboBox->currentText()));

}

void ConnectionOptionsFrame::setData(const QVariantMap& _data) {
  // Do nothing
}

bool ConnectionOptionsFrame::isEnabled() const {
  return true;
}

bool ConnectionOptionsFrame::needToRestartApplication() const {
  return false;
}

bool ConnectionOptionsFrame::canAccept() const {
  if (m_ui->m_remoteRadio->isChecked()) {
    return isIpOrHostName(m_ui->remoteNodesComboBox->currentText().split(":")[0]);
  } else {
    return true;
  }
}

void ConnectionOptionsFrame::setCryptoNoteAdapter(ICryptoNoteAdapter* _cryptoNoteAdapter) {
  m_cryptoNoteAdapter = _cryptoNoteAdapter;
}

void ConnectionOptionsFrame::remoteHostNameChanged(const QString& _host) {
  if (m_ui->m_remoteRadio->isChecked()) {
    bool res = isIpOrHostName(_host);
    Q_EMIT disableAcceptButtonSignal(!res);
  } else {
    Q_EMIT disableAcceptButtonSignal(false);
  }
}

void ConnectionOptionsFrame::connectionButtonClicked(int _buttonId) {
  remoteHostNameChanged(m_ui->remoteNodesComboBox->currentText().split(":")[0]);
}

void ConnectionOptionsFrame::addNodeClicked() {
  QUrl url = QUrl::fromUserInput(m_ui->remoteNodesComboBox->currentText());
  QString host = url.host();
  quint16 port = url.port(Settings::instance().getLocalRpcPort());
  if (isIpOrHostName(host)) {
    int index = m_ui->remoteNodesComboBox->findData(host);
    if (index == -1) {
      m_nodeModel->addNode(host, port);
    }
  } else {
    // error highlight
  }
  m_ui->addNodeButton->setEnabled(false);
  m_ui->removeNodeButton->setEnabled(m_ui->remoteNodesComboBox->count() != 0);
}

void ConnectionOptionsFrame::removeNodeClicked() {
  m_nodeModel->removeRow(m_ui->remoteNodesComboBox->currentIndex());
  Settings::instance().setRemoteNodeList(m_nodeModel->stringList());
  m_ui->removeNodeButton->setEnabled(m_ui->remoteNodesComboBox->count() != 0);
  remoteHostNameChanged(m_ui->remoteNodesComboBox->currentText().split(":")[0]);
}

void ConnectionOptionsFrame::remoteNodesComboChanged(const QString& _host) {
  QUrl url = QUrl::fromUserInput(m_ui->remoteNodesComboBox->currentText());
  QString host = url.host();
  int index = m_ui->remoteNodesComboBox->findData(host);
  if (index == -1 && isIpOrHostName(host)) {
    m_ui->addNodeButton->setEnabled(true);
  }
}

}
