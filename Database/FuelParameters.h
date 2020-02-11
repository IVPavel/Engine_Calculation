#ifndef FUELPARAMETERS_H
#define FUELPARAMETERS_H

#include <QDialog>

struct FuelParameters {
    int rowid;

    QString name;

    double Cv,
           Cp,
           Cvg,
           Cpg,
           k,
           kg,
           L0;

    FuelParameters(int rowid_P, QString name_P, double Cv_P, double Cp_P, double Cvg_P, double Cpg_P, double k_P, double kg_P, double L0_P);

    FuelParameters();
};

#endif // FUELPARAMETERS_H
