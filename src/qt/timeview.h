#ifndef TIMEVIEW_H
#define TIMEVIEW_H

#include <QWidget>

namespace Ui {
class TimeView;
}

class TimeView : public QWidget
{
    Q_OBJECT

public:
    explicit TimeView(QWidget *parent = 0);
    ~TimeView();

private:
    Ui::TimeView *ui;
};

#endif // TIMEVIEW_H
