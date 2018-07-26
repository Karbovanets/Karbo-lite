// Copyright (c) 2015-2017, The Karbovanets developers
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

#pragma once

#include <QDialog>
#include "IWalletAdapter.h"

namespace Ui {
class MnemonicDialog;
}

namespace WalletGui {

class MnemonicDialog : public QDialog {
  Q_OBJECT
  Q_DISABLE_COPY(MnemonicDialog)

public:
  MnemonicDialog(const AccountKeys& _keys, QWidget* _parent);
  ~MnemonicDialog();

private:
  QScopedPointer<Ui::MnemonicDialog> m_ui;
  AccountKeys m_keys;

  void initLanguages();
  void getMnemonic(QString _lang);

  Q_SLOT void languageChanged();

};

}
