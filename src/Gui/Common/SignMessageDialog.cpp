// Copyright (c) 2016-2019 The Karbowanec developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "SignMessageDialog.h"
#include "ui_SignMessageDialog.h"

#include <QClipboard>
#include <QFileDialog>
#include <QTextStream>
#include <QTabWidget>

#include <boost/utility/value_init.hpp>

#include <CryptoNoteConfig.h>
#include <CryptoNoteCore/CryptoNoteBasicImpl.h>

namespace WalletGui {

SignMessageDialog::SignMessageDialog(ICryptoNoteAdapter* _cryptoNoteAdapter, const AccountKeys& _keys, const QString& _address, QWidget* _parent) :
    QDialog(_parent, static_cast<Qt::WindowFlags>(Qt::WindowCloseButtonHint)), m_ui(new Ui::SignMessageDialog), m_keys(_keys), m_address(_address), m_cryptoNoteAdapter(_cryptoNoteAdapter) {
  m_ui->setupUi(this);
  m_ui->m_verificationResult->setText("");
}

SignMessageDialog::~SignMessageDialog() {
}

void SignMessageDialog::sign() {
  m_ui->m_tabWidget->setCurrentIndex(0);
  changeTitle(0);
}

void SignMessageDialog::verify() {
  m_ui->m_tabWidget->setCurrentIndex(1);
  changeTitle(1);
}

void SignMessageDialog::changeTitle(int _variant) {
  this->setWindowTitle(_variant == 0 ? tr("Sign message") : tr("Verify signed message"));
}

void SignMessageDialog::messageChanged() {
  if (m_ui->m_tabWidget->currentIndex() != 0) { return; }
  QString message = m_ui->m_messageEdit->toPlainText();
  QString _signature = m_cryptoNoteAdapter->getNodeAdapter()->getWalletAdapter()->signMessage(message);
  m_ui->m_signatureEdit->setText(_signature);
}

void SignMessageDialog::verifyMessage() {
  m_ui->m_verificationResult->setText("");
  CryptoNote::AccountPublicAddress acc = boost::value_initialized<CryptoNote::AccountPublicAddress>();
  QString address = m_ui->m_addressEdit->text().trimmed();
  QString message = m_ui->m_verifyMessageEdit->toPlainText();
  QString signature = m_ui->m_verifySignatureEdit->toPlainText();
  if(address.isEmpty() || message.isEmpty() || signature.isEmpty())
    return;
  uint64_t prefix;
  if(CryptoNote::parseAccountAddressString(prefix, acc, address.toStdString()) && prefix == CryptoNote::parameters::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX) {
      if (m_cryptoNoteAdapter->getNodeAdapter()->getWalletAdapter()->verifyMessage(message, address, signature)) {
        m_ui->m_verificationResult->setText(tr("Signature is valid"));
        m_ui->m_verificationResult->setStyleSheet("QLabel { color : green; }");
      } else {
        m_ui->m_verificationResult->setText(tr("Signature is invalid!"));
        m_ui->m_verificationResult->setStyleSheet("QLabel { color : red; }");
      }
  } else {
    m_ui->m_verificationResult->setText(tr("Address is invalid!"));
    m_ui->m_verificationResult->setStyleSheet("QLabel { color : red; }");
  }
}

}
