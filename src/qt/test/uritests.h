// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2015 The Hivemind Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef HIVEMIND_QT_TEST_URITESTS_H
#define HIVEMIND_QT_TEST_URITESTS_H

#include <QObject>
#include <QTest>

class URITests : public QObject
{
    Q_OBJECT

private slots:
    void uriTests();
};

#endif // HIVEMIND_QT_TEST_URITESTS_H
