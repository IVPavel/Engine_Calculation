#ifndef THERMOPHYSICALPARAMETERS_H
#define THERMOPHYSICALPARAMETERS_H

#include <QDialog>
#include "fuel.h"
#include "Database/DatabaseManager.h"
#include "dialogtpp.h"

namespace Ui {
class ThermophysicalParameters;
}

class ThermophysicalParameters : public QDialog
{
    Q_OBJECT

    QString getNameDialogP;
    int selectIndex;

private:
    void reloadDataWidgetList(QVector<FuelParameters> array);

public:
    explicit ThermophysicalParameters(QWidget *parent = 0);
    ~ThermophysicalParameters();

private slots:
    void on_pushButton_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_savaFuelToDB_clicked();

    void on_pushButton_loadFuel_clicked();

    void on_pushButton_deleteFuel_clicked();

signals:
    void setNewThermophisicalParametersSignal(Fuel fuel);

public slots:
    void setDBManegerSlot(DatabaseManager *setDatabse);
    void setNameForFuelSlot(QString name);

private:
    Ui::ThermophysicalParameters *ui;
    DialogTpP dialog;

    DatabaseManager *database;
    QVector<FuelParameters> fuelArray;
};

#endif // THERMOPHYSICALPARAMETERS_H
