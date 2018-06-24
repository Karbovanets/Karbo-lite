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

#pragma once

#include <QFrame>

#include "IOptionsPage.h"
#include "Application/IWalletUiItem.h"
#include "Models/NodeModel.h"

namespace Ui {
  class ConnectionOptionsFrame;
}

namespace WalletGui {

class NodeModel;

class ConnectionOptionsFrame : public QFrame, public IOptionsPage, public IWalletUiItem {
  Q_OBJECT
  Q_DISABLE_COPY(ConnectionOptionsFrame)

public:
  explicit ConnectionOptionsFrame(QWidget* _parent = nullptr);
  ~ConnectionOptionsFrame();

  // IOptionsPage
  virtual void load() override;
  virtual void save() override;
  virtual void setData(const QVariantMap& _data) override;
  virtual bool isEnabled() const override;
  virtual bool needToRestartApplication() const override;
  virtual bool canAccept() const override;

  // IWalletUiItem
  virtual void setCryptoNoteAdapter(ICryptoNoteAdapter* _cryptoNoteAdapter) override;

private:
  QScopedPointer<Ui::ConnectionOptionsFrame> m_ui;
  ICryptoNoteAdapter* m_cryptoNoteAdapter;
  NodeModel* m_nodeModel;

  Q_SLOT void remoteHostNameChanged(const QString& _host);
  Q_SLOT void remoteNodesComboChanged(const QString& _host);
  Q_SLOT void connectionButtonClicked(int _buttonId);
  Q_SLOT void addNodeClicked();
  Q_SLOT void removeNodeClicked();

Q_SIGNALS:
  void showRestartWarningSignal(bool _show) override;
  void disableAcceptButtonSignal(bool _disable) override;
};

}
