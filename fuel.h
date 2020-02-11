#ifndef FUEL_H
#define FUEL_H

class Fuel {
public:
    double Cv,    // теплоемкость Cv при сжатии, Дж/(кг*К)
           Cp,    // теплоемкость Cp при сжатии
           k,     // показатель адиабаты при сжатии
           Cvg,   // теплоемкость Cv при сгорании-расширении
           Cpg,   // теплоемкость Cp при сгорании-расширении
           kg,    // показатель адиабаты при сгорании-расширении
           L0;    // теоретически необходимое количество воздуха при сгорании 1 кг топлива, кмоль/кг
public:
    Fuel(double Cv, double Cp, double k, double Cvg, double Cpg, double kg, double L0);
    Fuel();
};

#endif // FUEL_H
