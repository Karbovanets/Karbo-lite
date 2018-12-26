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

#include <QTreeView>

namespace WalletGui {

class LinkLikeColumnDelegate;

class WalletTreeView : public QTreeView {
  Q_OBJECT
  Q_DISABLE_COPY(WalletTreeView)

public:
  explicit WalletTreeView(QWidget* _parent);
  virtual ~WalletTreeView();

  void setLinkLikeColumnSet(const QSet<int>& _linkLikeColumnSet);
  void setCopyableColumnSet(const QSet<int>& _copyableColumnSet);
  void setHoverIsVisible(bool _hoverIsVisible);
  void updateRowCount();
  void setAutoUpdateRowCount(bool _autoUpdateRowCount);

  virtual void setModel(QAbstractItemModel* _model) override;

protected:
  virtual void mouseMoveEvent(QMouseEvent* _event) override;
  virtual void paintEvent(QPaintEvent* _event) override;
  virtual void resizeEvent(QResizeEvent* _event) override;

private:
  QSet<int> m_linkLikeColumnSet;
  QSet<int> m_copyableColumnSet;
  LinkLikeColumnDelegate* m_linkLikeColumnDelegate;
  bool m_autoUpdateRowCount;

  void itemClicked(const QModelIndex& _index);
  int calculateVisibleRowCount() const;

Q_SIGNALS:
  void copyableItemClickedSignal(const QModelIndex& _index);
};

}
