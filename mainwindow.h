#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

#include <QDebug>
#include <QFileInfo>
#include "ThermophysicalIndicators.h"
#include "thermophysicalparameters.h"
#include "Database/DatabaseManager.h"
#include "buildgraphic.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    DatabaseManager database;
    QVector<EngineParameters> engineArray;

private slots:
    void reloadDataWidgetList(QVector<EngineParameters> array);

    void on_toCalculate_clicked();

    void on_radioButton_Petrol_clicked();

    void on_radioButton_Diesel_clicked();

    void on_saveAsCSV_clicked();

    void add_toTableView();

    void on_radioButton_4StrokeEngine_clicked();

    void on_radioButton_2StrokeEngine_clicked();

    int step_printTable();

    void on_savaToDB_clicked();

    void on_radioButton_In_lineEngine_clicked();

    void on_radioButton_V_shaped_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_pushButton_deleteEngine_clicked();

    void on_pushButton_loadEngine_clicked();

    void on_radioButton_Other_clicked();

    void on_thermoPhishicButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_build_graphic_clicked();

signals:
    void getDBManegerSignal(DatabaseManager *database);
    void setThermIndSignal(int num);

public slots:
    void setNewThermophisicalParametersSlot(Fuel);

private:
    Ui::MainWindow *ui;
    ThermophysicalParameters *_thermophysicalParameters;
    //BuildGraphic *buildgraphic;
};

#endif // MAINWINDOW_H
