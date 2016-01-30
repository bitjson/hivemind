#include "marketmodel.h"

extern CMarketTreeDB *pmarkettree;

MarketModel::MarketModel(QObject *parent) :
   QAbstractTableModel(parent)
{
}

int MarketModel::rowCount(const QModelIndex & /*parent*/) const
{
   return marketModel.size();
}

int MarketModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant MarketModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant MarketModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

void MarketModel::setBranch(uint256 branchID)
{
    // Make sure the branch exists
    const marketBranch *branch = pmarkettree->GetBranch(branchID);
    if (!branch) return;

    // Grab markets on the branch
    vector<marketMarket *> markets = pmarkettree->GetMarkets(branchID);

    // Add markets to the model
    beginInsertRows(QModelIndex(), 0, markets.size());

    for (unsigned int i = 0; i < markets.size(); i++) {
        marketModel.push_back(markets.at(i));
    }

    endInsertRows();
}

void MarketModel::resetModel()
{
    beginResetModel();

    marketModel.clear();

    endResetModel();
}
