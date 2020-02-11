#include "EngineParameters.h"

EngineParameters::EngineParameters(int id_P, QString name_Engine_P, QString strokeEngine_P, QString configureEngine_P, int HuT_P,
                                   double m1_P, double i_P, double D_P, double Fn_P, double rk_P, double lambda_P, double Fnn_P, double Fk_P,
                                   double Vc_P, double Pk_P, double Tk_P, int fiC_P, int fiZ_P, double omega_P, double a_P, double mtc_P,
                                   double Tw_P, double Pa_P, double Ta_P, double ma_P, double Va_P, double m_A_P, double mKKD_P,
                                   double Cv_P, double Cp_P, double Cvg_P, double Cpg_P, double k_P, double kg_P, double L0_P) {
    id = id_P;
    fiC = fiC_P;
    fiZ = fiZ_P;
    name_Engine = name_Engine_P;
    strokeEngine = strokeEngine_P;
    configureEngine = configureEngine_P;
    HuT = HuT_P;
    m1 = m1_P;
    i = i_P;
    D = D_P;
    Fn = Fn_P;
    rk = rk_P;
    lambda = lambda_P;
    Fnn = Fnn_P;
    Fk = Fk_P;
    Vc = Vc_P;
    Pk = Pk_P;
    Tk = Tk_P;
    omega = omega_P;
    a = a_P;
    mtc = mtc_P;
    Tw = Tw_P;
    Pa = Pa_P;
    Ta = Ta_P;
    ma = ma_P;
    Va = Va_P;
    m_A = m_A_P;
    mKKD = mKKD_P;
    Cv = Cv_P;
    Cp = Cp_P;
    Cvg = Cvg_P;
    Cpg = Cpg_P;
    k = k_P;
    kg = kg_P;
    L0 = L0_P;
}

EngineParameters::EngineParameters() {

}
