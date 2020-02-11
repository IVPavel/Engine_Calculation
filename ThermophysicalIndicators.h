#ifndef THERMOPHYSICAL_INDICATORS_H
#define THERMOPHYSICAL_INDICATORS_H

#include "Fuel.h"
#include "qmath.h"
#include <QVector>

#define ELEMENT_IN_ARRAY 721
#define R 278           // газовая постаянная, Дж/(кг*К)
#define PAtm 101300     // атмосферное давление, Па         // wikipedia = PAtm = 101325

class ThermophysicalIndicators
{
public:
    int fi,
        fiC,                   // Угол начала сгорания
        fiZ,                   // Угол конца сгорания
        HuT,                   // Теплота сгорания топлива
        numCylinders,          // Количество цилиндров

        step;                  // Шаг для вывода в таблице

    double m1,                 // показатель процесса сгорания
           cylDiam,            // диаметр цилиндра
           crankRad,           // радиус кривошипа
           lambda,             // отношение crankRad/Lш
           Pk,                 // давление наддува
           Tk,                 // температура наддувочного воздуха
           omega,              // угловая скорость вала
           alpha,              // коэффициент избытка воздуха
           Tw,                 // средняя температура стенок
           Pa,                 // давление
           Ta,                 // температура
           mass,               // масса поступательно движущих частей (преведенная)
           mechEff,            // механический КПД
          //############################################################################
           Hu,                 //??
           P,                  //??
           P2,                 //??
           alphaW,
           T,
           dQw,
           dQc,
           dT,
           Li,
           L1,

           areaPist,          // площадь поршня
           areaExPist,        // площадь теплообмена поршня
           areaExCap,         // площадь теплообмена кришки
           Vc,                // объем камеры сжатия
           cyclFuel,          // цикловая подача топлива
           ma,                // масса рабочего тела
           Va,                // объем рабочей полости
           V,
           dV,
           m,
           FteplSum,
           dm,
           dx,

           pi,
           KKDi,
           gi;

public:
      Fuel fuel;

public:
    //int array_fi[ELEMENT_IN_ARRAY];
    QVector<int> array_fi;
    QVector<double> array_P,
                    array_T,
                    array_m,
                    array_V,
                    array_alphaW,
                    array_FteplSum,
                    array_dV,
                    array_dQw,
                    array_dx,
                    array_dQc,
                    array_dm,
                    array_dT,
                    array_P2,
                    array_L1,
                    array_Li;
//    double array_P[ELEMENT_IN_ARRAY],
//           array_T[ELEMENT_IN_ARRAY],
//           array_m[ELEMENT_IN_ARRAY],
//           array_V[ELEMENT_IN_ARRAY],
//           array_alphaW[ELEMENT_IN_ARRAY],
//           array_FteplSum[ELEMENT_IN_ARRAY],
//           array_dV[ELEMENT_IN_ARRAY],
//           array_dQw[ELEMENT_IN_ARRAY],
//           array_dx[ELEMENT_IN_ARRAY],
//           array_dQc[ELEMENT_IN_ARRAY],
//           array_dm[ELEMENT_IN_ARRAY],
//           array_dT[ELEMENT_IN_ARRAY],
//           array_P2[ELEMENT_IN_ARRAY],
//           array_L1[ELEMENT_IN_ARRAY],
//           array_Li[ELEMENT_IN_ARRAY];

public:
    ThermophysicalIndicators(int c_fiC, int c_fiZ, int c_HuT, int c_numCylinders,
                             double c_m1, double c_cylDiam, double c_crankRad, double c_lambda, double c_Pk,
                             double c_Tk, double c_omega, double c_alpha, double c_Tw, double c_Pa, double c_Ta,
                             double c_mass, double c_areaPist, double c_areaExPist, double c_areaExCap,
                             double c_Vc, double c_cyclFuel, double c_ma, double c_Va,
                             Fuel _fuel);
    ThermophysicalIndicators();

    void calc();
};

struct ThermParameters
{
    int array_fi[ELEMENT_IN_ARRAY];
    double array_P[ELEMENT_IN_ARRAY],
           array_T[ELEMENT_IN_ARRAY],
           array_m[ELEMENT_IN_ARRAY],
           array_V[ELEMENT_IN_ARRAY],
           array_alphaW[ELEMENT_IN_ARRAY],
           array_FteplSum[ELEMENT_IN_ARRAY],
           array_dV[ELEMENT_IN_ARRAY],
           array_dQw[ELEMENT_IN_ARRAY],
           array_dx[ELEMENT_IN_ARRAY],
           array_dQc[ELEMENT_IN_ARRAY],
           array_dm[ELEMENT_IN_ARRAY],
           array_dT[ELEMENT_IN_ARRAY],
           array_P2[ELEMENT_IN_ARRAY],
           array_L1[ELEMENT_IN_ARRAY],
           array_Li[ELEMENT_IN_ARRAY];
};

#endif // THERMOPHYSICAL_INDICATORS_H














