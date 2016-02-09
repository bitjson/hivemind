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

void MarketTradeView::on_pushButtonFinalize_clicked()
{
    extern json_spirit::Value createtrade(const json_spirit::Array &params, bool fHelp);

    // Grab params from the UI
    std::string address = "";
    std::string marketID = "";
    std::string type = (ui->radioButtonLong->isChecked())? "buy":"sell";
    // TODO: get the correct number based on trade type
    double shares = ui->doubleSpinBoxQuickBuy->value();
    double price = 0.0;
    int state = 0;
    int nonce = 0;

    // Create params spirit array
    json_spirit::Array params;

    // Try to create trade
    json_spirit::Value result;
    try {
        result = createtrade(params, false);
    } catch (const std::runtime_error &error) {
        QString errorText = QString::fromStdString(error.what());
//        emit finalizeError(errorText);
    } catch (const std::exception &exception) {
        QString exceptionText = QString::fromStdString(exception.what());
//        emit finalizeError(exceptionText);
    } catch (const json_spirit::Object &object) {
        result = object;
    }

}
