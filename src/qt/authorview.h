#ifndef AUTHORVIEW_H
#define AUTHORVIEW_H

#include <QWidget>

class marketBranch;
class marketDecision;
class marketMarket;
class marketTrade;
class DecisionViewGraph;
class DecisionBranchWindow;
class DecisionDecisionWindow;
class DecisionMarketWindow;
class DecisionTradeWindow;
class WalletModel;

namespace Ui {
class AuthorView;
}

class AuthorView : public QWidget
{
    Q_OBJECT

public:
    explicit AuthorView(QWidget *parent = 0);
    ~AuthorView();

private slots:
    void on_pushButtonCreateCombo_clicked();

    void on_pushButtonCreateDecision_clicked();

    void on_pushButtonCreateMarket_clicked();

private:
    Ui::AuthorView *ui;
};

#endif // AUTHORVIEW_H
