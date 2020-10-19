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

#include <QUrl>
#include "CommonNodeAdapter.h"

namespace Logging {
  class ILogger;
}

namespace CryptoNote {
  class Currency;
}

namespace WalletGui {

class ProxyRpcNodeAdapter : public CommonNodeAdapter {
  Q_OBJECT
  Q_DISABLE_COPY(ProxyRpcNodeAdapter)

public:
  ProxyRpcNodeAdapter(const CryptoNote::Currency& _currency, Logging::ILogger& _loggerManager, Logging::ILogger& _walletLogger, const QUrl& _nodeUrl, QObject* _parent);
  virtual ~ProxyRpcNodeAdapter();

protected:
  virtual INodeAdapter* createWorker() const override;

private:
  const CryptoNote::Currency& m_currency;
  Logging::ILogger& m_loggerManager;
  Logging::ILogger& m_walletLogger;
  QUrl m_nodeUrl;
};

}
