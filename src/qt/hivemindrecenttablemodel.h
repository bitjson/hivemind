#ifndef HIVEMINDRECENTTABLEMODEL_H
#define HIVEMINDRECENTTABLEMODEL_H

#include "json/json_spirit_writer_template.h"
#include "txdb.h"

#include <QAbstractTableModel>
#include <QList>
#include <QTimer>

extern CMarketTreeDB *pmarkettree;

class HivemindRecentTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit HivemindRecentTableModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

signals:

public slots:

private slots:
    void updateModel();

private:
    QList<json_spirit::Array> recent;
    QTimer *pollTimer;

};

#endif // HIVEMINDRECENTTABLEMODEL_H
