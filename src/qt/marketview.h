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

private:
    Ui::MarketView *ui;

    MarketModel *marketModel;
    QTableView *marketTableView;
};

#endif // MARKETVIEW_H
