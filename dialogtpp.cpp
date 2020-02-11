#include "dialogtpp.h"
#include "ui_dialogtpp.h"
#include <QPushButton>

DialogTpP::DialogTpP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTpP)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Save)->setText("Зберегти");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Відміна");
}

DialogTpP::~DialogTpP()
{
    delete ui;
}

void DialogTpP::on_buttonBox_clicked(QAbstractButton *button) {

    if (button == ui->buttonBox->button(QDialogButtonBox::Save)) {
        emit getNameFuelSignal(ui->lineEdit->text());
    } else {
        emit getNameFuelSignal("");
    }

    ui->lineEdit->setText("");
}
