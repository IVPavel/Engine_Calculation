#include "buildgraphic.h"
#include "ui_buildgraphic.h"

//test
#include "ThermophysicalIndicators.h"
#include "qdebug.h"

BuildGraphic::BuildGraphic(QWidget *parent) : QDialog(parent),
    ui(new Ui::BuildGraphic)
{
    ui->setupUi(this);

    qDebug() << t;
}

BuildGraphic::~BuildGraphic() {
    delete ui;
}

void BuildGraphic::on_build_clicked() {
    //buildGraph(*array_m);
    for (int i = 0; i < tIndicatorsArray.count(); i++) {
        ui->comboBox->addItem(tIndicatorsArray[i].name);
    }
}

void BuildGraphic::buildGraph(QVector<double> array) {
    // add two new graphs and set their look:
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    //ui->widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    ui->widget->addGraph();
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(array.count()), y0(array.count());
    for (int i = 0; i < array.count(); i++)
    {
      x[i] = i;
      y0[i] = array[i]; // exponentially decaying cosine
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    ui->widget->xAxis2->setVisible(true);
    ui->widget->xAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    ui->widget->graph(0)->setData(x, y0);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    ui->widget->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    ui->widget->replot();
}

void BuildGraphic::on_pushButton_clicked()
{

}

//void BuildGraphic::thermIndSlot(int test) {
//    t = test;
//}
