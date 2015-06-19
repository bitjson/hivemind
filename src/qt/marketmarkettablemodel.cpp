// Copyright (c) 2015 The Truthcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "addresstablemodel.h"
#include "guiconstants.h"
#include "guiutil.h"
#include "marketmarkettablemodel.h"
#include "optionsmodel.h"
#include "primitives/market.h"
#include "scicon.h"
#include "walletmodel.h"

#include "main.h"
#include "sync.h"
#include "uint256.h"
#include "util.h"
#include "wallet.h"

#include <QColor>
#include <QDateTime>
#include <QDebug>
#include <QIcon>
#include <QList>


// Amount column is right-aligned it contains numbers
static int column_alignments[] = {
        Qt::AlignLeft|Qt::AlignVCenter, /* Address */
        Qt::AlignRight|Qt::AlignVCenter, /* B */
        Qt::AlignRight|Qt::AlignVCenter, /* TradingFee */
        Qt::AlignRight|Qt::AlignVCenter, /* MaxCommision */
        Qt::AlignLeft|Qt::AlignVCenter, /* Title */
        Qt::AlignLeft|Qt::AlignVCenter, /* Description */
        Qt::AlignLeft|Qt::AlignVCenter, /* Tags */
        Qt::AlignRight|Qt::AlignVCenter, /* Maturation */
    };


// Private implementation
class MarketMarketTablePriv
{
public:
    MarketMarketTablePriv(CWallet *wallet, MarketMarketTableModel *parent)
      : wallet(wallet),
        parent(parent)
    {
    }

    CWallet *wallet;
    MarketMarketTableModel *parent;

    /* Local cache of Marketes */
    QList<const marketMarket *> cached;

    int size()
    {
        return cached.size();
    }

    const marketMarket *index(int idx)
    {
        if(idx >= 0 && idx < cached.size())
            return cached[idx];
        return 0;
    }

    QString describe(const marketMarket *market, int unit)
    {
        return QString();
    }
};

MarketMarketTableModel::MarketMarketTableModel(CWallet *wallet, WalletModel *parent)
    : QAbstractTableModel(parent),
    wallet(wallet),
    walletModel(parent),
    priv(new MarketMarketTablePriv(wallet, this))
{
    columns
        << tr("Address")
        << tr("Liquidity Parameter")
        << tr("Trading Fee")
        << tr("Max Commission")
        << tr("Title")
        << tr("Description")
        << tr("Tags")
        << tr("Maturation")
        ;
}

MarketMarketTableModel::~MarketMarketTableModel()
{
    // unsubscribeFromCoreSignals();
    delete priv;
}

int MarketMarketTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return priv->size();
}

int MarketMarketTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return columns.length();
}

QVariant MarketMarketTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    const marketMarket *market = (const marketMarket *) index.internalPointer();

    switch(role)
    {
    case Qt::DisplayRole:
        switch(index.column())
        {
        case Address:
            return formatAddress(market);
        case B:
            return formatB(market);
        case TradingFee:
            return formatTradingFee(market);
        case MaxCommission:
            return formatMaxCommission(market);
        case Title:
            return formatTitle(market);
        case Description:
            return formatDescription(market);
        case Tags:
            return formatTags(market);
        case Maturation:
            return formatMaturation(market);
        default:
            ;
        }
        break;
    case AddressRole:
        return formatAddress(market);
    case TitleRole:
        return formatTitle(market);
    case DescriptionRole:
        return formatDescription(market);
    case TagsRole:
        return formatTags(market);
    case Qt::TextAlignmentRole:
        return column_alignments[index.column()];
    }
    return QVariant();
}

QVariant MarketMarketTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal)
    {
        if(role == Qt::DisplayRole)
            return columns[section];
        else
        if (role == Qt::TextAlignmentRole)
            return column_alignments[section];
        else
        if (role == Qt::ToolTipRole)
        {
            switch(section)
            {
            case Address:
                return tr("Address");
            case B:
                return tr("Liquidity Parameter");
            case TradingFee:
                return tr("Trading Fee");
            case MaxCommission:
                return tr("Maximum Commission");
            case Title:
                return tr("Title");
            case Description:
                return tr("Description");
            case Tags:
                return tr("Tags");
            case Maturation:
                return tr("Maturation");
            }
        }
    }
    return QVariant();
}

const marketMarket *MarketMarketTableModel::index(int row) const
{
    return priv->index(row);
}

QModelIndex MarketMarketTableModel::index(int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    const marketMarket *market = priv->index(row);
    if (market)
        return createIndex(row, column, (void *)market);
    return QModelIndex();
}

Qt::ItemFlags MarketMarketTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void
MarketMarketTableModel::onDecisionChange(const marketBranch *branch, const marketDecision *decision)
{
    if (!priv || !branch || !decision)
        return;

    /* erase cache */
    if (priv->cached.size()) {
        beginRemoveRows(QModelIndex(), 0, priv->cached.size()-1);
        priv->cached.clear();
        endRemoveRows();
    }

    /* new vector of markets for cache */
    std::vector<const marketMarket *> vec;
    uint256 decisionid = decision->GetHash();
    std::map<uint256, marketMarket *>::const_iterator it;
    for(it=branch->markets.begin(); it != branch->markets.end(); it++) {
        const marketMarket *market = it->second;
        bool hasDecision = false;
        const vector<uint256> &decisionIDs = market->decisionIDs;
        for(uint32_t i=0; i < decisionIDs.size(); i++) {
            if (decisionIDs[i] != decisionid)
                continue;
            hasDecision = true;
            break;
        }
        if (!hasDecision)
            continue;
        vec.push_back(it->second);
    }

    /* insert into cache */
    if (vec.size() > 0) {
        beginInsertRows(QModelIndex(), 0, vec.size()-1);
        for(uint32_t i=0; i < vec.size(); i++)
            priv->cached.append(vec[i]);
        endInsertRows();
    }
}

QString formatAddress(const marketMarket *market)
{
    CTruthcoinAddress addr;
    if (addr.Set(market->keyID))
        return QString::fromStdString(addr.ToString());
    return QString("Address");
}

QString formatB(const marketMarket *market)
{
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%.8f", market->B*1e-8);
    return QString(tmp);
}

QString formatTradingFee(const marketMarket *market)
{
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%.8f", market->tradingFee*1e-8);
    return QString(tmp);
}

QString formatMaxCommission(const marketMarket *market)
{
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%.8f", market->maxCommission*1e-8);
    return QString(tmp);
}

QString formatTitle(const marketMarket *market)
{
    return QString::fromStdString(market->title);
}

QString formatDescription(const marketMarket *market)
{
    return QString::fromStdString(market->description);
}

QString formatTags(const marketMarket *market)
{
    return QString::fromStdString(market->tags);
}

QString formatMaturation(const marketMarket *market)
{
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%u", market->maturation);
    return QString(tmp);
}

QString formatDecisionIDs(const marketMarket *market)
{
    return QString("");
}

QString formatDecisionFunctionIDs(const marketMarket *market)
{
    return QString("");
}

QString formatAccountValue(const marketMarket *market)
{
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%.8f", market->account);
    return QString(tmp);
}

QString formatTxPoW(const marketMarket *market)
{
    char tmp[32];
    snprintf(tmp, sizeof(tmp), "%u", market->txPoW);
    return QString(tmp);
}

QString formatHash(const marketMarket *market)
{
    return QString::fromStdString(market->GetHash().ToString());
}

