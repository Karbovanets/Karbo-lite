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

#include "AddressBookDialog.h"
#include "Models/AddressBookModel.h"
#include "Gui/Common/RightAlignmentColumnDelegate.h"

#include "ui_AddressBookDialog.h"

namespace WalletGui {

AddressBookDialog::AddressBookDialog(QAbstractItemModel* _addressBookModel, QWidget* _parent) :
  QDialog(_parent, static_cast<Qt::WindowFlags>(Qt::WindowCloseButtonHint)), m_ui(new Ui::AddressBookDialog) {
  m_ui->setupUi(this);
  m_ui->m_addressBookView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
  m_ui->m_addressBookView->setModel(_addressBookModel);
  m_ui->m_addressBookView->setItemDelegateForColumn(AddressBookModel::COLUMN_ADDRESS, new RightAlignmentColumnDelegate(true, this));
  m_ui->m_addressBookView->header()->setSectionResizeMode(AddressBookModel::COLUMN_LABEL, QHeaderView::Fixed);
  m_ui->m_addressBookView->header()->setSectionResizeMode(AddressBookModel::COLUMN_ADDRESS, QHeaderView::Stretch);
  m_ui->m_addressBookView->header()->setSectionResizeMode(AddressBookModel::COLUMN_PAYMENT_ID, QHeaderView::Stretch);
  m_ui->m_addressBookView->header()->hideSection(AddressBookModel::COLUMN_DONATION);
  m_ui->m_addressBookView->header()->resizeSection(AddressBookModel::COLUMN_LABEL, 200);
  if (_addressBookModel->rowCount() > 0) {
    m_ui->m_addressBookView->setCurrentIndex(_addressBookModel->index(0, 0));
  }
}

AddressBookDialog::~AddressBookDialog() {
}

QString AddressBookDialog::getAddress() const {
  return m_ui->m_addressBookView->currentIndex().data(AddressBookModel::ROLE_ADDRESS).toString();
}

QString AddressBookDialog::getPaymentId() const {
  return m_ui->m_addressBookView->currentIndex().data(AddressBookModel::ROLE_PAYMENT_ID).toString();
}

}
