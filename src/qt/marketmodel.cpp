#include "marketmodel.h"

#include <sstream>

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
    return 3;
}

QVariant MarketModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return false;
    }

    int row = index.row();
    int col = index.column();

    switch(role) {
    case Qt::DisplayRole:
    {
        marketMarket *market = marketModel.at(row);

        // Title
        if (col == 0) {
            return QString::fromStdString(market->title);
        }

        // Graph
        if (col == 1) {
            return QString("Graph");
        }

        // Market Details
        if (col == 2) {
            std::stringstream sstream;
            sstream << "Title: " << market->title << std::endl;
            sstream << "Description: " << market->description << std::endl;
            sstream << "Tags: " << market->tags << std::endl;
            sstream << "Market ID: " << market->GetHash().GetHex() << std::endl;

            return QString::fromStdString(sstream.str());
        }
    }
    }

    return QVariant();
}

QVariant MarketModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch(section) {
            case 0:
                return QString("Title");
            case 1:
                return QString("Graph");
            case 2:
                return QString("Market Info");
            }
        }
    }

    return QVariant();
}

void MarketModel::setBranch(uint256 branchID)
{
    // Make sure the branch exists
    const marketBranch *branch = pmarkettree->GetBranch(branchID);
    if (!branch) return;

    // Get the list of decisions on the branch
    vector<marketDecision *> decisions = pmarkettree->GetDecisions(branchID);

    // Make a list of markets from every decision on the branch
    vector<marketMarket *> markets;

    for (unsigned int x = 0; x < decisions.size(); x++) {
        // Get the markets for this decision
        uint256 uDecision;
        uDecision.SetHex(decisions.at(x)->GetHash().GetHex());
        vector<marketMarket* > decisionMarkets = pmarkettree->GetMarkets(uDecision);

        // Add the markets to the markets vector
        for (unsigned int y = 0; y < decisionMarkets.size(); y++) {
            markets.push_back(decisionMarkets.at(y));
        }
    }

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

uint256 MarketModel::getMarketID(const QModelIndex &index)
{
    uint256 uMarket;

    if (!index.isValid()) {
        return uMarket;
    }

    uMarket = marketModel.at(index.row())->GetHash();
    return uMarket;
}
