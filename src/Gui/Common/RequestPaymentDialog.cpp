// Copyright (c) 2016 The Karbowanec developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QFileDialog>
#include <QTextStream>
#include <QClipboard>
#include <QBuffer>
#include <QTime>
#include "ICryptoNoteAdapter.h"
#include "Gui/Common/QRLabel.h"
#include "RequestPaymentDialog.h"
#include "ui_RequestPaymentDialog.h"

namespace WalletGui {

RequestPaymentDialog::RequestPaymentDialog(ICryptoNoteAdapter* _cryptoNoteAdapter, const QString& _address, QWidget* _parent) : QDialog(_parent), m_ui(new Ui::RequestPaymentDialog), m_cryptoNoteAdapter(nullptr) {
  m_ui->setupUi(this);
  m_cryptoNoteAdapter = _cryptoNoteAdapter;
  m_address = _address;
  m_ui->m_amountSpinBox->setSuffix(" " + m_cryptoNoteAdapter->getCurrencyTicker().toUpper());
  generateRequest();
}

RequestPaymentDialog::~RequestPaymentDialog() {
}

void RequestPaymentDialog::generateRequest() {
  m_request = "karbowanec:" + m_address;
  if(m_cryptoNoteAdapter->parseAmount(m_ui->m_amountSpinBox->cleanText()) != 0){
    m_request.append("?amount=" + m_ui->m_amountSpinBox->cleanText());
  }

  if(m_cryptoNoteAdapter->parseAmount(m_ui->m_amountSpinBox->cleanText()) != 0 && !m_ui->m_paymentIdEdit->text().isEmpty()) {
    m_request.append("&payment_id=" + m_ui->m_paymentIdEdit->text());
  } else if(!m_ui->m_paymentIdEdit->text().isEmpty()) {
    m_request.append("?payment_id=" + m_ui->m_paymentIdEdit->text());
  }

  if((m_cryptoNoteAdapter->parseAmount(m_ui->m_amountSpinBox->cleanText()) != 0 || !m_ui->m_paymentIdEdit->text().isEmpty()) && !m_ui->m_payerLabelEdit->text().isEmpty()) {
    m_request.append("&label=" + QUrl::toPercentEncoding(m_ui->m_payerLabelEdit->text()));
  } else if(!m_ui->m_payerLabelEdit->text().isEmpty()){
    m_request.append("?label=" + QUrl::toPercentEncoding(m_ui->m_payerLabelEdit->text()));
  }
  m_ui->m_requestEdit->setText(m_request);
  m_ui->m_qrCodeLabel->showQRCode(m_request);
}

void RequestPaymentDialog::copyRequest() {
  QApplication::clipboard()->setText(m_request);
}

void RequestPaymentDialog::saveRequest() {
  QString file = QFileDialog::getSaveFileName(this, tr("Save as"), QDir::homePath(), "TXT (*.txt)");
  if (!file.isEmpty()) {
    QFile f(file);
    if (f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
      QTextStream outputStream(&f);
      outputStream << m_request;
      f.close();
    }
  }
}

void RequestPaymentDialog::saveQrCode() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save QR Code"), QDir::homePath(), "PNG (*.png)");
  if (!fileName.isEmpty()) {
    QPixmap qrcode = QPixmap::grabWidget(m_ui->m_qrCodeLabel);
    QFile f(fileName);
    if (f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
      QByteArray ba;
      QBuffer buffer(&ba);
      buffer.open(QIODevice::WriteOnly);
      qrcode.save(&buffer, "PNG");
      f.write(ba);
      f.close();
    }
  }
}

void RequestPaymentDialog::generatePaymentIdClicked() {
  QTime time = QTime::currentTime();
  qsrand((uint)time.msec());
  const QString possibleCharacters("ABCDEF0123456789");
  const int randomStringLength = 64;
  QString randomString;
  for(int i=0; i<randomStringLength; ++i)
  {
    int index = qrand() % possibleCharacters.length();
    QChar nextChar = possibleCharacters.at(index);
    randomString.append(nextChar);
  }
  m_ui->m_paymentIdEdit->setText(randomString);
}

}
