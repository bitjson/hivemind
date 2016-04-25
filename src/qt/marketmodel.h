#ifndef MARKETMODEL_H
#define MARKETMODEL_H

#include <QAbstractTableModel>
#include "uint256.h"
#include "txdb.h"
#include <string>

class MarketModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MarketModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:
    void setBranch(uint256 branchID);
    void resetModel();
    uint256 getMarketID(const QModelIndex &index);

private:
    QList<marketMarket *> marketModel;
    QList<QPixmap *> graphPixmapList;

};

#endif // MARKETMODEL_H
