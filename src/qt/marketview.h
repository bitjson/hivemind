#ifndef MARKETVIEW_H
#define MARKETVIEW_H

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
};

#endif // MARKETVIEW_H
