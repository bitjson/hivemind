#ifndef MARKETTRADEVIEW_H
#define MARKETTRADEVIEW_H

#include <QWidget>

namespace Ui {
class MarketTradeView;
}

class MarketTradeView : public QWidget
{
    Q_OBJECT

public:
    explicit MarketTradeView(QWidget *parent = 0);
    ~MarketTradeView();

private:
    Ui::MarketTradeView *ui;
};

#endif // MARKETTRADEVIEW_H
