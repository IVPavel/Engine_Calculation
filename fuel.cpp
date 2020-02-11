#include "fuel.h"

Fuel::Fuel() {
    Cv = 0;
    Cp = 0;
    k = 0;
    Cvg = 0;
    Cpg = 0;
    kg = 0;
    L0 = 0;
}

Fuel::Fuel(double _Cv, double _Cp, double _k, double _Cvg, double _Cpg, double _kg, double _L0) {
    Cv = _Cv;
    Cp = _Cp;
    k = _k;
    Cvg = _Cvg;
    Cpg = _Cpg;
    kg = _kg;
    L0 = _L0;
}
