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
    /*
     * Creating votes goes as follows;
     * 1. Create reveal vote object.
     * 2. Create sealed vote object from revealed vote object.
     */
    extern json_spirit::Value createrevealvote(const json_spirit::Array &revealVoteParams, bool fHelp);
    extern json_spirit::Value createsealedvote(const json_spirit::Array &sealedVoteParams, bool fHelp);

    /* 1. Create reveal vote object */

    // Get reveal vote params from UI
    std::string address = ui->lineEditAddress->text().toStdString();
    std::string branchID = ui->lineEditBranchID->text().toStdString();
    int height = ui->spinBoxHeight->value();
    std::string voteID = "";
    int NA = 2016;
    std::string decisionID = ui->lineEditDecisionID->text().toStdString();
    int vote = 0;

    // Create spirit array of reveal vote params
    json_spirit::Array revealVoteParams;
    revealVoteParams.push_back(address);
    revealVoteParams.push_back(branchID);
    revealVoteParams.push_back(height);
    revealVoteParams.push_back(voteID);
    revealVoteParams.push_back(NA);
    revealVoteParams.push_back(decisionID);
    revealVoteParams.push_back(vote);

    // Try to create the revealed vote
    json_spirit::Value revealVoteResult;
    try {
        revealVoteResult = createrevealvote(revealVoteParams, false);
    } catch (const std::runtime_error &error) {
        std::cout << "Error: " << error.what() << std::endl;
        return;
    } catch (const std::exception &exception) {
        std::cout << "Exception: " << exception.what() << std::endl;
        return;
    } catch (const json_spirit::Object &object) {
        revealVoteResult = object;
    }

    // Check the reveal vote results
    std::string resultVoteID = "";
    try {
        // Get reveal vote result pairs
        json_spirit::Object revealVoteResultObject = revealVoteResult.get_obj();
        json_spirit::Pair codePair = revealVoteResultObject[0];
        json_spirit::Pair messagePair = revealVoteResultObject[1];

        // If error, get error code and message
        if (codePair.name_ == "code") {
            int code = codePair.value_.get_int();
            if (code < 0) {
                std::cout << "Error creating reveal vote: " << messagePair.value_.get_str() << std::endl;
            }
        }

        // If success, get the txid and reveal vote id
        std::cout << "codepair name: " << codePair.name_ << std::endl;
        std::cout << "codepair value: " << codePair.value_.get_str() << std::endl;

        std::cout << "messagepair name: " << messagePair.name_ << std::endl;
        std::cout << "messagepair value: " << messagePair.value_.get_str() << std::endl;
    } catch (const std::runtime_error &error) {
        std::cout << "Error: " << error.what() << std::endl;
    } catch (const std::exception &exception) {
        std::cout << "Exception: " << exception.what() << std::endl;
    }

    /* 2. Create sealed vote object from revealed vote object */

    // Create spirit array of sealed vote params
    json_spirit::Array sealedVoteParams;
    sealedVoteParams.push_back(branchID);
    sealedVoteParams.push_back(height);
    sealedVoteParams.push_back(resultVoteID);


    // Try to create the sealed vote
    json_spirit::Value sealedVoteResult;
    try {
        sealedVoteResult = createsealedvote(sealedVoteParams, false);
    } catch (const std::runtime_error &error) {
        std::cout << "Error: " << error.what() << std::endl;
        return;
    } catch (const std::exception &exception) {
        std::cout << "Exception: " << exception.what() << std::endl;
        return;
    } catch (const json_spirit::Object &object) {
        sealedVoteResult = object;
    }

    // Check the sealed vote result
    try {
        // Get sealed vote result pairs
        json_spirit::Object sealedVoteResultObject = sealedVoteResult.get_obj();
        json_spirit::Pair codePair = sealedVoteResultObject[0];
        json_spirit::Pair messagePair = sealedVoteResultObject[1];

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
