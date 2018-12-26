// Copyright (c) 2015-2017, The Bytecoin developers
// Copyright (c) 2017-2018, The Karbo developers
//
// This file is part of Karbo.
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

#include "Gui/Common/GlassFrame.h"

class QLabel;

namespace WalletGui {

class OverviewHeaderGlassFrame : public GlassFrame {
  Q_OBJECT
  Q_DISABLE_COPY(OverviewHeaderGlassFrame)

public:
  OverviewHeaderGlassFrame(QMovie* _syncMovie, QWidget* _parent);
  ~OverviewHeaderGlassFrame();

  virtual void install(QWidget* _parent);
  virtual void remove();

private:
  QLabel* m_syncLabel;
};

}
