#ifndef DIALOGTPP_H
#define DIALOGTPP_H

#include <QDialog>
#include "qabstractbutton.h"

namespace Ui {
class DialogTpP;
}

class DialogTpP : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTpP(QWidget *parent = 0);
    ~DialogTpP();

signals:
    void getNameFuelSignal(QString name);

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogTpP *ui;
};

#endif // DIALOGTPP_H
