#ifndef MARKETTRADEVIEW_H
#define MARKETTRADEVIEW_H

#include "json/json_spirit_writer_template.h"

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

private slots:
    void on_pushButtonFinalize_clicked();

private:
    Ui::MarketTradeView *ui;
};

#endif // MARKETTRADEVIEW_H
