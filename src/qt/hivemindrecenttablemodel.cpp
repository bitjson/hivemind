#include "hivemindrecenttablemodel.h"

#include <QTimer>

#define NUM_ITEMS 6

HivemindRecentTableModel::HivemindRecentTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

    /*
     * the table should have these columns;
     * 1. Type / icon (market / vote etc)
     * 2. Title
     * 3. Height
     */

    // This timer will update the recent hivemind model
    pollTimer = new QTimer(this);
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(updateModel()));
    pollTimer->start(1000);
}

int HivemindRecentTableModel::rowCount(const QModelIndex & /*parent*/) const
{
    return recent.size();
}

int HivemindRecentTableModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

QVariant HivemindRecentTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return false;
    }

    int row = index.row();
    int col = index.column();

    switch (role) {
    case Qt::DisplayRole:
    {
        /* Display recent entries to the hivemind market branch */

        // Icon
        if (col == 0) {
            return "Icon";
        }

        // Title
        if (col == 1) {
            return "Title";
        }

        // Height
        if (col == 2) {
            return 0;
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
                return QString("Height");
            }
        }
    }
    return QVariant();
}

void HivemindRecentTableModel::updateModel()
{
    // on refresh, if the 6th item isn't the same as tip of market branch still (nothing new), get the
    // NUM_ITEMS --6-- most recent things on the pmarket branch

}
