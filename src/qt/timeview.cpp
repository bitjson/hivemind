#include "timeview.h"
#include "ui_timeview.h"

TimeView::TimeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeView)
{
    ui->setupUi(this);
}

TimeView::~TimeView()
{
    delete ui;
}
