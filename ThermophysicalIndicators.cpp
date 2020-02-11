#include "ThermophysicalIndicators.h"

ThermophysicalIndicators::ThermophysicalIndicators(int c_fiC, int c_fiZ, int c_HuT, int c_numCylinders,
                                                   double c_m1, double c_cylDiam, double c_crankRad, double c_lambda, double c_Pk,
                                                   double c_Tk, double c_omega, double c_alpha, double c_Tw, double c_Pa, double c_Ta,
                                                   double c_mass, double c_areaPist, double c_areaExPist, double c_areaExCap,
                                                   double c_Vc, double c_cyclFuel, double c_ma, double c_Va,
                                                   Fuel _fuel) {
    fiC = c_fiC;
    fiZ = c_fiZ;
    HuT = c_HuT;
    numCylinders = c_numCylinders;
    m1 = c_m1;
    cylDiam = c_cylDiam;
    crankRad = c_crankRad;
    lambda = c_lambda;
    Pk = c_Pk;
    Tk = c_Tk;
    omega = c_omega;
    alpha = c_alpha;
    Tw = c_Tw;
    Pa = c_Pa;
    Ta = c_Ta;
    mass = c_mass;
    areaPist = c_areaPist;
    areaExPist = c_areaExPist;
    areaExCap = c_areaExCap;
    Vc = c_Vc;
    cyclFuel = c_cyclFuel;
    ma = c_ma;
    Va = c_Va;
    //fuel
    fuel.Cv = _fuel.Cv;
    fuel.Cp = _fuel.Cp;
    fuel.k = _fuel.k;
    fuel.Cvg = _fuel.Cvg;
    fuel.Cpg = _fuel.Cpg;
    fuel.kg = _fuel.kg;
    fuel.L0 = _fuel.L0;
}

ThermophysicalIndicators::ThermophysicalIndicators() {
    fiC = 0;
    fiZ = 0;
    HuT = 0;
    numCylinders = 0;
    m1 = 0;
    cylDiam = 0;
    crankRad = 0;
    lambda = 0;
    Pk = 0;
    Tk = 0;
    omega = 0;
    alpha = 0;
    Tw = 0;
    Pa = 0;
    Ta = 0;
    mass = 0;
    areaPist = 0;
    areaExPist = 0;
    areaExCap = 0;
    Vc = 0;
    cyclFuel = 0;
    ma = 0;
    Va = 0;
    //fuel
    //Cv = 0;
    //Cp = 0;
    //k = 0;
    //Cvg = 0;
    //Cpg = 0;
    //kg = 0;
    //L0 = 0;
}

void ThermophysicalIndicators::calc() {
    if (alpha > 1) {
        Hu = double(HuT);
    } else {
        Hu = double(HuT) - (120 * 1000000  * (1 - alpha) * fuel.L0);
    }

    for (fi = 0; fi <= 720; fi++) {
        double radToDeg = double(fi) / 180 * M_PI;

        if (fi == 0) {
            V = Vc;
            m = ma;
            Li = 0;
        } else {
            V = Vc + areaPist * crankRad * (1 - qCos(radToDeg) + lambda / 4 * (1 - qCos(2 * radToDeg)));
            dV = areaPist * crankRad * (qSin(radToDeg) + lambda * qSin(2 * radToDeg) / 2) * M_PI / 180;
        }

        if (fi < 180) {
            P = Pa;
            T = Ta;
        } else if (fi >= 540) {
            P = double(2 * PAtm) - Pa;
        } else {
            alphaW = 0.0068 * (3 + (Pk - double(PAtm)) / double(PAtm)) * qSqrt(P * T);
            FteplSum = areaExPist + areaExCap + M_PI * cylDiam * crankRad * (1 - qCos(radToDeg) + fuel.L0 / 4 * (1 - qCos(2 * radToDeg)));
            dQw = alphaW * FteplSum * (Tw - T) * M_PI / 180 / omega;

            // fiC = 340 / fiZ = 390
            if (fi >= fiC && fi <= fiZ) {
                double preDX1 = powf(double(fi - fiC) / double(fiZ - fiC), m1);
                double preDX2 = powf(double(fi - fiC) / double(fiZ - fiC), m1 + 1);

                dx = 6.908 * ((m1 + 1) / double(fiZ - fiC)) * preDX1 * (qExp(-6.908 * preDX2)) * 1;

                dQc = Hu * cyclFuel * dx;
                dm = cyclFuel * dx;
            } else {
                dx = 0;
                dQc = 0;

                dQc = Hu * cyclFuel * dx;
                dm = cyclFuel * dx;
            }

            if (fi <= 360) {
                dT = (dQc + dQw) / (fuel.Cv * m) - (T * dm / m) - (fuel.k - 1) * T * dV / V;
            } else {
                dT = (dQc + dQw) / (fuel.Cvg * m) - (T * dm / m) - (fuel.kg - 1) * T * dV / V;
            }

            P2 = P;
            m = m + dm;
            T = T + dT;
            P = double(R) * m * T / V;
            L1 = ((P2 + P) / 2 - double(PAtm)) * dV;
            Li = Li + L1;
        }

        //array_fi[fi] = fi;
        array_fi.append(fi);
        //array_P[fi] = P;
        array_P.append(P);
        array_T.append(T);
        array_m.append(m);
        array_V.append(V);
        array_alphaW.append(alphaW);
        array_FteplSum.append(FteplSum);
        array_dV.append(dV);
        array_dQw.append(dQw);
        array_dx.append(dx);
        array_dQc.append(dQc);
        array_dm.append(dm);
        array_dT.append(dT);
        array_P2.append(P2);
        array_L1.append(L1);
        array_Li.append(Li);
//        array_T[fi] = T;
//        array_m[fi] = m;
//        array_V[fi] = V;
//        array_alphaW[fi] = alphaW;
//        array_FteplSum[fi] = FteplSum;
//        array_dV[fi] = dV;
//        array_dQw[fi] = dQw;
//        array_dx[fi] = dx;
//        array_dQc[fi] = dQc;
//        array_dm[fi] = dm;
//        array_dT[fi] = dT;
//        array_P2[fi] = P2;
//        array_L1[fi] = L1;
//        array_Li[fi] = Li;
    }

    pi = Li / (double(2) * crankRad * areaPist);
    KKDi= Li / (Hu * cyclFuel);
    gi = double(3600000) / (KKDi  * Hu);
}
