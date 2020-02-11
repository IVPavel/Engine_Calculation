#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlQueryModel>
//#include "QtSql/QSqlDatabase"
#include <QtSql>
#include "QSqlQuery"
#include "QSqlError"
#include <typeinfo>

#include "EngineParameters.h"
#include "FuelParameters.h"

const QString fuelPList = "name, Cv, Cp, Cvg, Cpg, k, kg, L0";
const QString enginePList = "id, name_Engine, StrokeEngine, configureEngine, HuT, m1, i, "
                            "D, Fn, rk, lambda, Fnn, Fk, Vc, Pk, Tk, fic, fiz, omega, a, mtc, "
                            "Tw, Pa, Ta, ma, Va, m_A, mKKD, Cv, Cp, Cvg, Cpg, k, kg, L0";

const QString tableEngine = "engine";
const QString tableFuel = "fuel";

class DatabaseManager {
private:
    QSqlDatabase database;

public:
    DatabaseManager(QString *appPath);
    DatabaseManager();

    QVector<EngineParameters> getEngineParameters();
    QVector<FuelParameters> getFuelParameters();

    void deleteParameters(int rowid, QString table);
    void saveParametersEngine(EngineParameters *param);
    void saveParametersFuel(FuelParameters *param);
};

#endif // DATABASE_
