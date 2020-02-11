#include "DatabaseManager.h"
#include "qdebug.h"
#include <QtGlobal>

enum paramEngineList {id_L, name_Engine_L, strokeEngine_L,
                configureEngine_L, HuT_L, m1_L, i_L, D_L,
                Fn_L, rk_L, lambda_L, Fnn_L, Fk_L, Vc_L, Pk_L,
                Tk_L, fiC_L, fiZ_L, omega_L, a_L, mtc_L, Tw_L,
                Pa_L, Ta_L, ma_L, Va_L, m_A_L, mKKD_L, Cv_L,
                Cp_L, Cvg_L, Cpg_L, k_L, kg_L, L0_L};

enum paramFuleList {name_FL, Cv_FL, Cp_FL, Cvg_FL, Cpg_FL, k_FL, kg_FL, L0_FL};

DatabaseManager::DatabaseManager(QString *appPath) {
    QString typeDatabase = "QSQLITE";
    QString nameDatabseFile = "\\database.db";

    //Подключаем базу данных
    QSqlDatabase database = QSqlDatabase::addDatabase(typeDatabase);
    database.setHostName("host");
    database.setDatabaseName(*appPath + nameDatabseFile);

    database.open();
}

DatabaseManager::DatabaseManager() {}

QVector<EngineParameters> DatabaseManager::getEngineParameters() {
    QVector<EngineParameters> parameters;

    QSqlQuery query;
    query.prepare("SELECT rowid, * FROM " + tableEngine);
    if(query.exec()) {
        while(query.next()) {
            parameters.append(EngineParameters(query.value(id_L).toInt(),
                                               query.value(name_Engine_L + 1).toString(),
                                               query.value(strokeEngine_L + 1).toString(),
                                               query.value(configureEngine_L + 1).toString(),
                                               query.value(HuT_L + 1).toDouble(),
                                               query.value(m1_L + 1).toDouble(),
                                               query.value(i_L + 1).toDouble(),
                                               query.value(D_L + 1).toDouble(),
                                               query.value(Fn_L + 1).toDouble(),
                                               query.value(rk_L + 1).toDouble(),
                                               query.value(lambda_L + 1).toDouble(),
                                               query.value(Fnn_L + 1).toDouble(),
                                               query.value(Fk_L + 1).toDouble(),
                                               query.value(Vc_L + 1).toDouble(),
                                               query.value(Pk_L + 1).toDouble(),
                                               query.value(Tk_L + 1).toDouble(),
                                               query.value(fiC_L + 1).toInt(),
                                               query.value(fiZ_L + 1).toInt(),
                                               query.value(omega_L + 1).toDouble(),
                                               query.value(a_L + 1).toDouble(),
                                               query.value(mtc_L + 1).toDouble(),
                                               query.value(Tw_L + 1).toDouble(),
                                               query.value(Pa_L + 1).toDouble(),
                                               query.value(Ta_L + 1).toDouble(),
                                               query.value(ma_L + 1).toDouble(),
                                               query.value(Va_L + 1).toDouble(),
                                               query.value(m_A_L + 1).toDouble(),
                                               query.value(mKKD_L + 1).toDouble(),
                                               query.value(Cv_L + 1).toDouble(),
                                               query.value(Cp_L + 1).toDouble(),
                                               query.value(Cvg_L + 1).toDouble(),
                                               query.value(Cpg_L + 1).toDouble(),
                                               query.value(k_L + 1).toDouble(),
                                               query.value(kg_L + 1).toDouble(),
                                               query.value(L0_L + 1).toDouble()));
        }
    }

    return parameters;
}

QVector<FuelParameters> DatabaseManager::getFuelParameters() {
    QVector<FuelParameters> parameters;

    QSqlQuery query;
    query.prepare("SELECT rowid, * FROM " + tableFuel);
    if(query.exec()) {
        while(query.next()) {
            parameters.append(FuelParameters(query.value(0).toInt(),
                                             query.value(name_FL + 1).toString(),
                                             query.value(Cv_FL + 1).toDouble(),
                                             query.value(Cp_FL + 1).toDouble(),
                                             query.value(Cvg_FL + 1).toDouble(),
                                             query.value(Cpg_FL + 1).toDouble(),
                                             query.value(k_FL + 1).toDouble(),
                                             query.value(kg_FL + 1).toDouble(),
                                             query.value(L0_FL + 1).toDouble()));
        }
    }

    return parameters;
}

void DatabaseManager::deleteParameters(int rowid, QString tableName) {
    QString toStringRowId = QString::number(rowid);
    QSqlQuery query;
    query.exec("DELETE FROM "+tableName+" WHERE rowid = " + toStringRowId);
}

void DatabaseManager::saveParametersEngine(EngineParameters *param) {
    QSqlQuery query;

    QString values;
    EngineParameters *p = param;
    values = "'"+QString().number(p->id)+"', '"+p->name_Engine+"', '"+p->strokeEngine+"', '"+p->configureEngine+"', "
             "'"+QString().number(p->HuT)+"', '"+QString().number(p->m1)+"', '"+QString().number(p->i)+"', '"+QString().number(p->D)+"',"
             " '"+QString().number(p->Fn)+"', '"+QString().number(p->rk)+"', '"+QString().number(p->lambda)+"', '"+QString().number(p->Fnn)+"',"
             " '"+QString().number(p->Fk)+"', '"+QString().number(p->Vc)+"', '"+QString().number(p->Pk)+"', '"+QString().number(p->Tk)+"', "
             "'"+QString().number(p->fiC)+"', '"+QString().number(p->fiZ)+"', '"+QString().number(p->omega)+"', '"+QString().number(p->a)+"',"
             " '"+QString().number(p->mtc)+"', '"+QString().number(p->Tw)+"', '"+QString().number(p->Pa)+"', '"+QString().number(p->Ta)+"', "
             "'"+QString().number(p->ma)+"', '"+QString().number(p->Va)+"', '"+QString().number(p->m_A)+"', '"+QString().number(p->mKKD)+"', "
             "'"+QString().number(p->Cv)+"', '"+QString().number(p->Cp)+"', '"+QString().number(p->Cvg)+"', '"+QString().number(p->Cpg)+"', "
             "'"+QString().number(p->k)+"', '"+QString().number(p->kg)+"', '"+QString().number(p->L0)+"'";

    query.prepare("INSERT INTO  engine ("+enginePList+") VALUES ("+values+")");
    query.exec();
}

void DatabaseManager::saveParametersFuel(FuelParameters *param) {
    QSqlQuery query;

    QString values;
    FuelParameters *p = param;
    values = "'"+p->name+"', '"+QString().number(p->Cv)+"', '"+QString().number(p->Cp)+"', '"+QString().number(p->Cvg)+"', "
             "'"+QString().number(p->Cpg)+"','"+QString().number(p->k)+"', '"+QString().number(p->kg)+"', '"+QString().number(p->L0)+"'";

    query.prepare("INSERT INTO  fuel ("+fuelPList+") VALUES ("+values+")");
    query.exec();
}
