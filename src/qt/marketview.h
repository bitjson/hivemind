#ifndef MARKETVIEW_H
#define MARKETVIEW_H

#include "marketmodel.h"

#include <QTableView>
#include <QWidget>

namespace Ui {
class MarketView;
}

class MarketView : public QWidget
{
    Q_OBJECT

public:
    explicit MarketView(QWidget *parent = 0);
    ~MarketView();

public slots:
        void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MarketView *ui;

    MarketModel *marketModel;
    QTableView *marketTableView;
};

#endif // MARKETVIEW_H
