#include "marketview.h"
#include "ui_marketview.h"

MarketView::MarketView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketView)
{
    ui->setupUi(this);
}

MarketView::~MarketView()
{
    delete ui;
}
