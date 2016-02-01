#include "markettradeview.h"
#include "ui_markettradeview.h"

MarketTradeView::MarketTradeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketTradeView)
{
    ui->setupUi(this);
}

MarketTradeView::~MarketTradeView()
{
    delete ui;
}
