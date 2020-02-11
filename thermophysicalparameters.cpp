#include "thermophysicalparameters.h"
#include "ui_thermophysicalparameters.h"

ThermophysicalParameters::ThermophysicalParameters(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThermophysicalParameters)
{
    ui->setupUi(this);

    fuelArray = database->getFuelParameters();
    reloadDataWidgetList(fuelArray);

    if (!fuelArray.isEmpty()) {
        ui->listWidget->setCurrentRow(0);
        on_listWidget_clicked(ui->listWidget->model()->index(0,0));
    }

}

ThermophysicalParameters::~ThermophysicalParameters()
{
    delete ui;

    reloadDataWidgetList(fuelArray);

//    double Cv,    // теплоемкость Cv при сжатии, Дж/(кг*К)
//           Cp,    // теплоемкость Cp при сжатии
//           k,     // показатель адиабаты при сжатии
//           Cvg,   // теплоемкость Cv при сгорании-расширении
//           Cpg,   // теплоемкость Cp при сгорании-расширении
//           kg,    // показатель адиабаты при сгорании-расширении
//           L0;    // теоретически необходимое количество воздуха при сгорании 1 кг топлива, кмоль/кг
}

void ThermophysicalParameters::on_pushButton_clicked() {
    Fuel fuel;

    //Считаем значение из первого lineEdit
    QString set_Cv = ui->str_Cv->text();
    //Переведем значение в число
    fuel.Cv = set_Cv.toDouble();
    //qDebug("Cv = %f", fuel.Cv);

    QString set_Cp = ui->str_Cp->text();
    fuel.Cp = set_Cp.toDouble();

    QString set_Cvg = ui->str_Cvg->text();
    fuel.Cvg = set_Cvg.toDouble();

    QString set_Cpg = ui->str_Cpg->text();
    fuel.Cpg = set_Cpg.toDouble();

    QString set_k = ui->str_k->text();
    fuel.k = set_k.toDouble();

    QString set_kg = ui->str_kg->text();
    fuel.kg = set_kg.toDouble();

    QString set_L0 = ui->str_L0->text();
    fuel.L0 = set_L0.toDouble();

    emit setNewThermophisicalParametersSignal(fuel);
}

void ThermophysicalParameters::setDBManegerSlot(DatabaseManager *setDatabse) {
    database = setDatabse;
}

void ThermophysicalParameters::reloadDataWidgetList(QVector<FuelParameters> array) {
    ui->listWidget->clear();
    for (int i = 0; i < array.count(); i++) {
        ui->listWidget->addItem(array[i].name);
    }
}

void ThermophysicalParameters::on_listWidget_clicked(const QModelIndex &index) {
    selectIndex = index.row();
    FuelParameters paramFuel = fuelArray[index.row()];
    ui->groupBox->setTitle(paramFuel.name);
    ui->label_Cv->setText(QString::number(paramFuel.Cv));
    ui->label_Cp->setText(QString::number(paramFuel.Cp));
    ui->label_Cvg->setText(QString::number(paramFuel.Cvg));
    ui->label_Cpg->setText(QString::number(paramFuel.Cpg));
    ui->label_k->setText(QString::number(paramFuel.k));
    ui->label_kg->setText(QString::number(paramFuel.kg));
    ui->label_L0->setText(QString::number(paramFuel.L0));
}

void ThermophysicalParameters::on_savaFuelToDB_clicked() {
    FuelParameters fuelPtrs;

    connect(&dialog, &DialogTpP::getNameFuelSignal, this, &ThermophysicalParameters::setNameForFuelSlot);
    dialog.setModal(true);
    dialog.exec();

    fuelPtrs.name = getNameDialogP;
    fuelPtrs.Cv = ui->str_Cv->text().toDouble();
    fuelPtrs.Cp = ui->str_Cp->text().toDouble();
    fuelPtrs.Cvg = ui->str_Cvg->text().toDouble();
    fuelPtrs.Cpg = ui->str_Cpg->text().toDouble();
    fuelPtrs.k = ui->str_k->text().toDouble();
    fuelPtrs.kg = ui->str_kg->text().toDouble();
    fuelPtrs.L0 = ui->str_L0->text().toDouble();

    if  (getNameDialogP == "") {
        return;
    } else {
        database->saveParametersFuel(&fuelPtrs);
        fuelArray = database->getFuelParameters();
        reloadDataWidgetList(fuelArray);
    }

    qDebug() << "save";
}

void ThermophysicalParameters::setNameForFuelSlot(QString name) {
    getNameDialogP = name;
}

void ThermophysicalParameters::on_pushButton_loadFuel_clicked() {
    ui->str_Cv->setText(QString().number(fuelArray[selectIndex].Cv));
    ui->str_Cp->setText(QString().number(fuelArray[selectIndex].Cp));
    ui->str_Cvg->setText(QString().number(fuelArray[selectIndex].Cvg));
    ui->str_Cpg->setText(QString().number(fuelArray[selectIndex].Cpg));
    ui->str_k->setText(QString().number(fuelArray[selectIndex].k));
    ui->str_kg->setText(QString().number(fuelArray[selectIndex].kg));
    ui->str_L0->setText(QString().number(fuelArray[selectIndex].L0));
}

void ThermophysicalParameters::on_pushButton_deleteFuel_clicked() {
    if (fuelArray[selectIndex].rowid == 1) {
        return;
    } else if (fuelArray[selectIndex].rowid == 2) {
        return;
    } else {
        database->deleteParameters(fuelArray[selectIndex].rowid, "fuel");
        fuelArray = database->getFuelParameters();
        reloadDataWidgetList(fuelArray);
    }
}
