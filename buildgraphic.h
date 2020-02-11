#ifndef BUILDGRAPHIC_H
#define BUILDGRAPHIC_H

#include <QDialog>
#include <QAbstractButton>
#include <thermind.h>

namespace Ui {
class BuildGraphic;
}

class BuildGraphic : public QDialog
{
    Q_OBJECT
public:
    int t;
public:
    QVector<ThermInd> tIndicatorsArray;

public:
    explicit BuildGraphic(QWidget *parent = 0);
    ~BuildGraphic();

private slots:
    void on_build_clicked();

    void on_pushButton_clicked();

public slots:
    //void thermIndSlot(int test);

private:
    void buildGraph(QVector<double> array);

private:
    Ui::BuildGraphic *ui;
};

#endif // BUILDGRAPHIC_H
