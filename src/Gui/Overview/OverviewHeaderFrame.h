// Copyright (c) 2015-2017, The Bytecoin developers
// Copyright (c) 2017-2020, The Karbo developers
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

#include <QFrame>

#include "Application/IWalletUiItem.h"
#include "ICryptoNoteAdapter.h"
#include "INodeAdapter.h"

class QDataWidgetMapper;
class QSortFilterProxyModel;

namespace Ui {
  class OverviewHeaderFrame;
}

namespace WalletGui {

class OverviewHeaderGlassFrame;

class OverviewHeaderFrame : public QFrame, public IWalletUiItem, 
  public INodeAdapterObserver, public ICryptoNoteAdapterObserver {
  Q_OBJECT
  Q_DISABLE_COPY(OverviewHeaderFrame)

public:
  explicit OverviewHeaderFrame(QWidget* _parent);
  ~OverviewHeaderFrame();

  // QObject
  virtual bool eventFilter(QObject* _object, QEvent* _event) override;

  // IWalletUiItem
  virtual void setCryptoNoteAdapter(ICryptoNoteAdapter* _cryptoNoteAdapter) override;
  virtual void setMainWindow(QWidget *_mainWindow) override;
  virtual void setNodeStateModel(QAbstractItemModel* _model) override;
  virtual void setWalletStateModel(QAbstractItemModel* _model) override;
  virtual void setTransactionPoolModel(QAbstractItemModel *_model) override;

  // INodeAdapterObserver
  Q_SLOT virtual void initCompleted(int _status) override;
  Q_SLOT virtual void deinitCompleted() override;
  Q_SLOT virtual void peerCountUpdated(quintptr _count) override;
  Q_SLOT virtual void localBlockchainUpdated(CryptoNote::BlockHeaderInfo _lastLocalBlockInfo) override;
  Q_SLOT virtual void lastKnownBlockHeightUpdated(quint32 _height) override;
  Q_SLOT virtual void connectionStatusUpdated(bool _connected) override;

  // ICryptoNoteAdapterObserver
  Q_SLOT virtual void cryptoNoteAdapterInitCompleted(int _status) override;
  Q_SLOT virtual void cryptoNoteAdapterDeinitCompleted() override;


private:
  QScopedPointer<Ui::OverviewHeaderFrame> m_ui;
  ICryptoNoteAdapter* m_cryptoNoteAdapter;
  QWidget* m_mainWindow;
  QAbstractItemModel* m_nodeStateModel;
  QAbstractItemModel* m_walletStateModel;
  QAbstractItemModel* m_transactionPoolModel;
  QSortFilterProxyModel* m_overViewTransactionPoolModel;
  QMovie* m_syncMovie;
  OverviewHeaderGlassFrame* m_balancesGlassFrame;
  OverviewHeaderGlassFrame* m_transactionPoolGlassFrame;

  bool m_isConnected = true;
  QString m_nodeHost;
  quint16 m_nodePort;

  void copyAvailableBalance();
  void copyLockedBalance();
  void copyTotalBalance();
  void transactionPoolChanged();
  void changeConnectionStateAppearance();
  void walletStateModelDataChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles);
  void m_nodeStateModelDataChanged(const QModelIndex& _topLeft, const QModelIndex& _bottomRight, const QVector<int>& _roles);

  void touchNodeInfo();

  Q_SLOT void poolTransactionClicked(const QModelIndex& _index);
};

}
