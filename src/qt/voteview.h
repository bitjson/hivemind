#ifndef VOTEVIEW_H
#define VOTEVIEW_H

#include <QWidget>

#include "json/json_spirit_writer_template.h"

namespace Ui {
class VoteView;
}

class VoteView : public QWidget
{
    Q_OBJECT

public:
    explicit VoteView(QWidget *parent = 0);
    ~VoteView();

private slots:
    void on_pushButtonCreateVote_clicked();

private:
    Ui::VoteView *ui;
};

#endif // VOTEVIEW_H
