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

#include <QDateTime>

#include "AboutDialog.h"
#include "Settings/Settings.h"
#include "version.h"
#include "CryptoNoteWalletConfig.h"

#include "ui_AboutDialog.h"

namespace WalletGui {

AboutDialog::AboutDialog(QWidget* _parent) : QDialog(_parent, static_cast<Qt::WindowFlags>(Qt::WindowCloseButtonHint)), m_ui(new Ui::AboutDialog) {
  m_ui->setupUi(this);

  QString aboutText = m_ui->m_aboutLabel->text();
  m_ui->m_aboutLabel->setText(aboutText.arg(CN_VERSION " (" GIT_REVISION ")")
                                       .arg(PROJECT_VERSION_LONG)
                                       .arg(QDateTime::currentDateTime().date().year()));
}

AboutDialog::~AboutDialog() {
}

}
