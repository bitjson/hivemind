#include "hivemindrecenttablemodel.h"

#include "scicon.h"

#include <QIcon>
#include <QTimer>

HivemindRecentTableModel::HivemindRecentTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

    /*
     * the table should have these columns;
     * 1. Type / icon (market / vote etc)
     * 2. Title
     * 3. Text
     * 4. Height
     */

    // This timer will update the recent hivemind model
    pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(updateModel()));
    pollTimer->start(10000);

    updateModel();
}

int HivemindRecentTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return recentDecisions.size();
}

int HivemindRecentTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 4;
}

QVariant HivemindRecentTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return false;
    }

    int row = index.row();
    int col = index.column();

    marketDecision *recentDecision = recentDecisions.at(row);

    /* Display recent entries to the hivemind market branch */
    switch (role) {
    case Qt::DecorationRole:
    {
        // Icon
        if (col == 0) {
            QPixmap decisionIcon(QPixmap(":/icons/decision").scaled(80, 80));
            return decisionIcon;
        }
    }
    case Qt::DisplayRole:
    {
        // Title
        if (col == 1) {
            return QString::fromStdString(recentDecision->prompt);
        }

        // Text
        if (col == 2) {
            return QString::fromStdString(recentDecision->ToString());
        }

        // Height
        if (col == 3) {
            return QString::number(recentDecision->nHeight);
        }
    }
    }
    return QVariant();
}

QVariant HivemindRecentTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Type/Icon");
            case 1:
                return QString("Title");
            case 2:
                return QString("Text");
            case 3:
                return QString("Height");
            }
        }
    }
    return QVariant();
}

void HivemindRecentTableModel::updateModel()
{
    /*
     * 1. Get Branches
     * 2. Get Decisions
     * 3. Get Trades
     * 4. Get Votes
     * 5. Sort data by most recent
     * 6. Display up to limit of items
     */

    // Clear old data
    beginResetModel();
    recentDecisions.clear();
    endResetModel();

    // Get branches
    // TODO get branches other than main. vector<marketBranch *> branches = pmarkettree->GetBranches();
    uint256 branchID;
    branchID.SetHex("0f894a25c5e0318ee148fe54600ebbf50782f0a1df1eb2aab06321a8ccec270d");

    // Get decisions
    vector<marketDecision *> decisions = pmarkettree->GetDecisions(branchID);

    int row = recentDecisions.size();
    beginInsertRows(QModelIndex(), row, row+decisions.size());

    unsigned int displayCount = 20;
    if (decisions.size() < displayCount) displayCount = decisions.size();

    for (unsigned int i = 0; i < displayCount; ++i) {
        recentDecisions.push_back(decisions.at(i));
    }

    endInsertRows();

    // Get markets TODO

    // Get trades TODO

    // Get votes TODO
}
