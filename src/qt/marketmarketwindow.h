// Copyright (c) 2015 The Truthcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TRUTHCOIN_QT_MARKETMARKETWINDOW_H
#define TRUTHCOIN_QT_MARKETMARKETWINDOW_H

#include "guiutil.h"

#include <QDialog>
#include <QLabel>

class marketBranch;
class marketDecision;
class MarketMarketTableModel;
class MarketMarketFilterProxyModel;
class MarketView;
class WalletModel;

QT_BEGIN_NAMESPACE
class QLineEdit;
class QTableView;
QT_END_NAMESPACE

class MarketMarketWindow
    : public QDialog
{
    Q_OBJECT

public:
    enum ColumnWidths {
        ADDR_COLUMN_WIDTH = 180,
        B_COLUMN_WIDTH = 100,
        TRADINGFEE_COLUMN_WIDTH = 100,
        TITLE_COLUMN_WIDTH = 260,
        DESCRIPTION_COLUMN_WIDTH = 200,
        TAGS_COLUMN_WIDTH = 100,
        MATURATION_COLUMN_WIDTH = 60,
    };

    explicit MarketMarketWindow(QWidget *parent=0);
    void setModel(WalletModel *);
    void onDecisionChange(const marketBranch *, const marketDecision *);

private:
    QLineEdit *filterAddress;
    QLineEdit *filterTitle;
    QLineEdit *filterDescription;
    QLineEdit *filterTag;

    MarketView *marketView;
    MarketMarketTableModel *tableModel;
    QTableView *tableView;
    MarketMarketFilterProxyModel *marketMarketProxyModel;

public slots:
    void currentRowChanged(const QModelIndex &, const QModelIndex &);
    void filterAddressChanged(const QString &);
    void filterTitleChanged(const QString &);
    void filterDescriptionChanged(const QString &);
    void filterTagChanged(const QString &);
};

#endif // TRUTHCOIN_QT_MARKETMARKETWINDOW_H
