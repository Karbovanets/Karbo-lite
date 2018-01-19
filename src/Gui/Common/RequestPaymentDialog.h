// Copyright (c) 2016 The Karbowanec developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QDialog>
#include <QUrl>
#include "ICryptoNoteAdapter.h"
#include "Application/IWalletUiItem.h"

namespace Ui {
  class RequestPaymentDialog;
}

namespace WalletGui {

class ICryptoNoteAdapter;

class RequestPaymentDialog : public QDialog {
  Q_OBJECT
  Q_DISABLE_COPY(RequestPaymentDialog)

public:
  RequestPaymentDialog(ICryptoNoteAdapter* _cryptoNoteAdapter, const QString& _address, QWidget* _parent);
  ~RequestPaymentDialog();

private:
  QScopedPointer<Ui::RequestPaymentDialog> m_ui;
  ICryptoNoteAdapter* m_cryptoNoteAdapter;

  QString m_address;
  QString m_request;

  Q_SLOT void generatePaymentIdClicked();
  Q_SLOT void generateRequest();
  Q_SLOT void copyRequest();
  Q_SLOT void saveRequest();
  Q_SLOT void saveQrCode();
};

}
