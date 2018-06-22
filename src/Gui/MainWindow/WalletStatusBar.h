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

#include <QStatusBar>

#include "ICryptoNoteAdapter.h"
#include "INodeAdapter.h"
#include "IWalletAdapter.h"
#include "Application/IWalletUiItem.h"

class QLabel;

namespace WalletGui {

class WalletStatusBar : public QStatusBar, public IWalletUiItem, public IWalletAdapterObserver,
  public ICryptoNoteAdapterObserver {
  Q_OBJECT
  Q_DISABLE_COPY(WalletStatusBar)

public:
  explicit WalletStatusBar(QWidget* _parent);
  ~WalletStatusBar();

  // IWalletUiItem
  virtual void setCryptoNoteAdapter(ICryptoNoteAdapter* _cryptoNoteAdapter) override;
  virtual void setNodeStateModel(QAbstractItemModel* _model) override;
  virtual void updateStyle() override;

  // IWalletAdapterObserver
  Q_SLOT virtual void walletOpened() override;
  Q_SLOT virtual void walletOpenError(int _initStatus) override;
  Q_SLOT virtual void walletClosed() override;
  Q_SLOT virtual void passwordChanged() override;
  Q_SLOT virtual void synchronizationProgressUpdated(quint32 _current, quint32 _total) override;
  Q_SLOT virtual void synchronizationCompleted() override;
  Q_SLOT virtual void balanceUpdated(quint64 _actualBalance, quint64 _pendingBalance) override;
  Q_SLOT virtual void externalTransactionCreated(quintptr _transactionId, const FullTransactionInfo& _transaction) override;
  Q_SLOT virtual void transactionUpdated(quintptr _transactionId, const FullTransactionInfo& _transaction) override;

  // ICryptoNoteAdapterObserver
  Q_SLOT virtual void cryptoNoteAdapterInitCompleted(int _status) override;
  Q_SLOT virtual void cryptoNoteAdapterDeinitCompleted() override;

protected:
  virtual void timerEvent(QTimerEvent* _event) override;

private:
  ICryptoNoteAdapter* m_cryptoNoteAdapter;
  QAbstractItemModel* m_nodeStateModel;
  QLabel* m_syncStatusLabel;
  QLabel* m_syncStatusIconLabel;
  QLabel* m_encryptionStatusIconLabel;
  QLabel* m_connectionStateLabel;
  QLabel* m_connectionStateIconLabel;
  QMovie* m_syncMovie;
  bool m_walletIsSynchronized;
  bool m_isConnected = false;
  int m_checkSyncStateTimerId;

  void nodeStateChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles);
  void updateStatusDescription();
  void updateStatusConnection();
  void updateSyncState(bool _isSynchronized);
  void updateEncryptedState(bool _isEncrypted);
};

}
