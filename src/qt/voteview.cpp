#include "voteview.h"
#include "ui_voteview.h"

VoteView::VoteView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoteView)
{
    ui->setupUi(this);
}

VoteView::~VoteView()
{
    delete ui;
}

void VoteView::on_pushButtonCreateVote_clicked()
{
    // Get params from UI
    std::string address = ui->lineEditAddress->text().toStdString();
    std::string marketID = ui->lineEditMarketID->text().toStdString();
    std::string buySell = (ui->radioButtonBuy->isChecked()) ? "buy": "sell";
    double shares = ui->doubleSpinBoxShares->value();
    double price = ui->doubleSpinBoxPrice->value();
    int state = ui->spinBoxState->value();
    int nonce = ui->spinBoxNonce->value();

    // Create spirit array of vote params
    json_spirit::Array params;
    params.push_back(address);
    params.push_back(marketID);
    params.push_back(buySell);
    params.push_back(shares);
    params.push_back(price);
    params.push_back(state);
    params.push_back(nonce);

    extern json_spirit::Value createsealedvote(const json_spirit::Array &params, bool fHelp);

    /*
     *  TODO:
     * create revealed vote with zeros in place of vote id
     * create sealed vote from return value of revealed vote
     */

    // Try to create the vote
    json_spirit::Value result;
    try {
        result = createsealedvote(params, false);
    } catch (const std::runtime_error &error) {
        std::cout << "Error: " << error.what() << std::endl;
        return;
    } catch (const std::exception &exception) {
        std::cout << "Exception: " << exception.what() << std::endl;
        return;
    } catch (const json_spirit::Object &object) {
        result = object;
    }

    // Check the result
    try {
        // Get result pairs
        json_spirit::Object resultObject = result.get_obj();
        json_spirit::Pair codePair = resultObject[0];
        json_spirit::Pair messagePair = resultObject[1];

        // If error, get error code and message
        if (codePair.name_ == "code") {
            int code = codePair.value_.get_int();
            if (code < 0) {
                std::cout << "Error creating vote: " << messagePair.value_.get_str() << std::endl;
            }
        }

        // If success, get the txid and vote id
        std::cout << "codepair name: " << codePair.name_ << std::endl;
        std::cout << "codepair value: " << codePair.value_.get_str() << std::endl;

        std::cout << "messagepair name: " << messagePair.name_ << std::endl;
        std::cout << "messagepair value: " << messagePair.value_.get_str() << std::endl;

    } catch (const std::runtime_error &error) {
        std::cout << "Error: " << error.what() << std::endl;
    } catch (const std::exception &exception) {
        std::cout << "Exception: " << exception.what() << std::endl;
    }
}
