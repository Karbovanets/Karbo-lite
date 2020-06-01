// Copyright (c) 2016-2019 The Karbowanec developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QDialog>
#include "IWalletAdapter.h"
#include "ICryptoNoteAdapter.h"

namespace Ui {
class SignMessageDialog;
}

namespace WalletGui {

class IWalletAdapter;
class ICryptoNoteAdapter;

class SignMessageDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(SignMessageDialog)

public:
    SignMessageDialog(ICryptoNoteAdapter* _cryptoNoteAdapter, const AccountKeys& _keys, const QString& _address, QWidget * _parent);
    SignMessageDialog(QWidget *_parent);
    void sign();
    void verify();

    ~SignMessageDialog();

private:
    QString m_address;
    AccountKeys m_keys;
    bool m_verify;

    Q_SLOT void messageChanged();
    Q_SLOT void verifyMessage();
    Q_SLOT void changeTitle(int _variant);

    ICryptoNoteAdapter* m_cryptoNoteAdapter;

    QScopedPointer<Ui::SignMessageDialog> m_ui;
};

}
