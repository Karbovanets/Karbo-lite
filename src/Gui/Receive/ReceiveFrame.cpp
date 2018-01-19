// Copyright (c) 2016-2018, The Karbo developers
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

#include <QMouseEvent>
#include <QThread>

#ifdef Q_OS_WIN
#include <stdint.h>
#endif

#include "Settings/Settings.h"
#include "ReceiveFrame.h"
#include "ui_ReceiveFrame.h"

namespace WalletGui {

ReceiveFrame::ReceiveFrame(QWidget* _parent) : QFrame(_parent), m_ui(new Ui::ReceiveFrame),
  m_cryptoNoteAdapter(nullptr), m_mainWindow(nullptr) {
  m_ui->setupUi(this);
}

ReceiveFrame::~ReceiveFrame() {
}

void ReceiveFrame::setCryptoNoteAdapter(ICryptoNoteAdapter* _cryptoNoteAdapter) {
  m_cryptoNoteAdapter = _cryptoNoteAdapter;
  m_cryptoNoteAdapter->addObserver(this);
}

void ReceiveFrame::setMainWindow(QWidget* _mainWindow) {
  m_mainWindow = _mainWindow;
}

void ReceiveFrame::cryptoNoteAdapterInitCompleted(int _status) {
  if (_status == 0) {
  }
}

void ReceiveFrame::cryptoNoteAdapterDeinitCompleted() {
  // Do nothing
}

}
