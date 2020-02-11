#ifndef THERMIND_H
#define THERMIND_H

#include <QVector>

class ThermInd {
public:
    QString name;
    QVector<double> *array;

public:
    ThermInd(QString nameInsert, QVector<double> *arrayInsert);

    ThermInd();
};

#endif // THERMIND_H
