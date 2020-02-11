#include "BuildGraphWindow.h"
#include "ui_BuildGraphWindow.h"

#include "QDebug"

BuildGraphWindow::BuildGraphWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuildGraphWindow)
{
    ui->setupUi(this);

    qDebug() << t;
}

BuildGraphWindow::~BuildGraphWindow()
{
    delete ui;
}
