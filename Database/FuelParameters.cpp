#include "FuelParameters.h"

FuelParameters::FuelParameters(int rowid_P, QString name_P, double Cv_P, double Cp_P, double Cvg_P, double Cpg_P, double k_P, double kg_P, double L0_P)
{
    rowid = rowid_P;
    name = name_P;
    Cv = Cv_P;
    Cp = Cp_P;
    Cvg = Cvg_P;
    Cpg = Cpg_P;
    k = k_P;
    kg = kg_P;
    L0 = L0_P;
}

FuelParameters::FuelParameters() {

}
