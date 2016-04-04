#include "voteview.h"
#include "ui_voteview.h"

#include <QDialog>

#include <iostream>
#include "base58.h"
#include "txdb.h"

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

void VoteView::on_pushButtonSelectDecision_clicked()
{
    // Grab the ID of the user selected branch
    QString branchID;
    if (ui->comboBoxBranch->currentText() == "Main") {
        branchID = "0f894a25c5e0318ee148fe54600ebbf50782f0a1df1eb2aab06321a8ccec270d";
    }

    // Exit if no branch is selected (technically impossible via the UI)
    if (branchID.isEmpty()) return;

    // Grab the branch
    uint256 uBranch;
    uBranch.SetHex(branchID.toStdString());
    const marketBranch *branch = pmarkettree->GetBranch(uBranch);

    if (!branch) return;

    // Grab decisions on the branch
    vector<marketDecision *> decisions = pmarkettree->GetDecisions(uBranch);

    // Setup the decision selection widget
    decisionSelection = new DecisionSelectionView(this);
    QVector<marketDecision *> qvDecisions = QVector<marketDecision *>::fromStdVector(decisions);
    QList<marketDecision *> qlDecisions = QList<marketDecision *>::fromVector(qvDecisions);
    decisionSelection->loadDecisions(qlDecisions);

    // Connect signals
    connect(decisionSelection, SIGNAL(decisionSelected(QString)),
            this, SLOT(decisionSelected(QString)));

    // Display the decision selection widget
    QHBoxLayout *hbox = new QHBoxLayout(this);
    hbox->addWidget(decisionSelection);
    QDialog *dialog = new QDialog(this);

    connect(decisionSelection, SIGNAL(done()),
            dialog, SLOT(close()));

    dialog->setWindowTitle("Select Decision");
    dialog->setLayout(hbox);
    dialog->exec();
}

void VoteView::decisionSelected(QString decisionHex)
{
    ui->lineEditDecisionID->setText(decisionHex);
}

void VoteView::on_pushButtonCreateRevealVote_clicked()
{

}

void VoteView::on_pushButtonCreateSealedVote_clicked()
{
    /*
     * Creating votes goes as follows;
     * 1. Create reveal vote object.
     * 2. Create sealed vote object from revealed vote object.
     */
    extern json_spirit::Value createsealedvote(const json_spirit::Array &sealedVoteParams, bool fHelp);

    /* 1. Create reveal vote object */

    // Grab the branch if it exists
    std::string branchID = "0f894a25c5e0318ee148fe54600ebbf50782f0a1df1eb2aab06321a8ccec270d";
    uint256 uBranch;
    uBranch.SetHex(branchID);
    marketBranch *branch = pmarkettree->GetBranch(uBranch);
    if (!branch) {
        std::cout << "Branch does not exist\n";
        return;
    }

    // Create blank voteid
    std::string voteID = "0000000000000000000000000000000000000000000000000000000000000000";
    uint256 uVote;
    uVote.SetHex(voteID);

    // Grab the decision if it exists
    std::string decisionID = ui->lineEditDecisionID->text().toStdString();
    uint256 uDecision;
    uDecision.SetHex(decisionID);
    marketDecision *decision = pmarkettree->GetDecision(uDecision);
    if (!decision) {
        std::cout << "Decision does not exist\n";
        return;
    }

    // Create Votecoin address
    CHivemindAddress address;
    address.is_votecoin = 1;
    CScriptID id = branch->GetScript();
    address.Set(id);

    // Create revealvote
    marketRevealVote revealVote;
    revealVote.branchid.SetHex(branch->GetHash().GetHex());
    revealVote.height = ui->spinBoxHeight->value();
    revealVote.voteid = uVote;
    revealVote.decisionIDs.push_back(decision->GetHash());
    revealVote.decisionVotes.push_back(ui->comboBoxVote->currentIndex());
    revealVote.NA = 2016;
    address.GetKeyID(revealVote.keyID);

    /* 2. Create sealed vote object from revealed vote object */

    // Create spirit array of sealed vote params
    json_spirit::Array sealedVoteParams;
    sealedVoteParams.push_back(branch->GetHash().GetHex());
    sealedVoteParams.push_back(ui->spinBoxHeight->value());
    sealedVoteParams.push_back(revealVote.GetHash().GetHex());

    // Try to create the sealedvote
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
