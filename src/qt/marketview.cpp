#include "marketview.h"
#include "ui_marketview.h"

MarketView::MarketView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketView)
{
    ui->setupUi(this);

    QString branchID = "0f894a25c5e0318ee148fe54600ebbf50782f0a1df1eb2aab06321a8ccec270d";

    // Grab the branch
    uint256 uBranch;
    uBranch.SetHex(branchID.toStdString());

    // Setup model & market table
    marketTableView = new QTableView(this);
    marketTableView->horizontalHeader()->setStretchLastSection(true);
    marketTableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    marketTableView->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    marketModel = new MarketModel(this);
    marketTableView->setModel(marketModel);
    marketTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->frameRight->layout()->addWidget(marketTableView);

    // Set the branch for the market table model
    marketModel->setBranch(uBranch);

    // Setup signals
    connect(marketTableView, SIGNAL(doubleClicked(QModelIndex)),
            marketModel, SLOT(on_tableView_doubleClicked(QModelIndex)));
}

MarketView::~MarketView()
{
    delete ui;
}
