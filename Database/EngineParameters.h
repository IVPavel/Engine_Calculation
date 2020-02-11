#ifndef ENGINEPARAMETERS_H
#define ENGINEPARAMETERS_H

#include "qdebug.h"

struct EngineParameters {
    int id, fiC, fiZ, HuT;

    QString name_Engine,
            strokeEngine,
            configureEngine;

    double m1, i, D, Fn, rk,
           lambda, Fnn, Fk, Vc, Pk,
           Tk, omega, a,
           mtc, Tw, Pa, Ta, ma, Va, m_A, mKKD,
           Cv, Cp, Cvg, Cpg, k, kg, L0;

    EngineParameters(int id_P, QString name_Engine_P, QString strokeEngine_P, QString configureEngine_P, int HuT_P,
                     double m1_P, double i_P, double D_P, double Fn_P, double rk_P, double lambda_P, double Fnn_P, double Fk_P,
                     double Vc_P, double Pk_P, double Tk_P, int fiC_P, int fiZ_P, double omega_P, double a_P, double mtc_P,
                     double Tw_P, double Pa_P, double Ta_P, double ma_P, double Va_P, double m_A_P, double mKKD_P,
                     double Cv_P, double Cp_P, double Cvg_P, double Cpg_P, double k_P, double kg_P, double L0_P);

    EngineParameters();
};

#endif // ENGINEPARAMETERS_H
