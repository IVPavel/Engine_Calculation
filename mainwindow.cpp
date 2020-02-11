#include "mainwindow.h"
#include "ui_mainwindow.h"

//tabel
#include "QStandardItemModel"
#include "QStandardItem"
// save
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

#include <QtWebKit/QtWebKit>

#include <QDate>

#include "BuildGraphWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _thermophysicalParameters(NULL)//, buildgraphic(NULL)
{
    ui->setupUi(this);

    QString app_path = qApp->applicationDirPath();
    ui->webView->load(QUrl("file:///" + app_path + "/pdf/web/viewer.html"));
    database = DatabaseManager(&app_path);

    engineArray = database.getEngineParameters();

    reloadDataWidgetList(engineArray);

    if (!engineArray.isEmpty()) {
        ui->listWidget->setCurrentRow(0);
        on_listWidget_clicked(ui->listWidget->model()->index(0,0));
    }

    ui->build_graphic->setEnabled(false);

    on_radioButton_Petrol_clicked();
    on_radioButton_4StrokeEngine_clicked();
    on_radioButton_In_lineEngine_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString engineCycle;
QString configEng;
int startCycle, endCycle, tableLine;
int selectIndex;

ThermophysicalIndicators calcThermIndicators;

void MainWindow::reloadDataWidgetList(QVector<EngineParameters> array) {
    ui->listWidget->clear();
    for (int i = 0; i < array.count(); i++) {
        ui->listWidget->addItem(array[i].name_Engine);
    }
}

void MainWindow::on_radioButton_Petrol_clicked() {
    calcThermIndicators.fuel.Cv  = 727.6;
    calcThermIndicators.fuel.Cp  = 1014.6;
    calcThermIndicators.fuel.k   = 1.4;
    calcThermIndicators.fuel.Cvg = 954.1;
    calcThermIndicators.fuel.Cpg = 1241.1;
    calcThermIndicators.fuel.kg  = 1.3;
    calcThermIndicators.fuel.L0  = 0.516;
}

void MainWindow::on_radioButton_Diesel_clicked() {
    calcThermIndicators.fuel.Cv  = 740.5;
    calcThermIndicators.fuel.Cp  = 1027.5;
    calcThermIndicators.fuel.k   = 1.39;
    calcThermIndicators.fuel.Cvg = 905.5;
    calcThermIndicators.fuel.Cpg = 1192.5;
    calcThermIndicators.fuel.kg  = 1.32;
    calcThermIndicators.fuel.L0  = 0.500;
}

void MainWindow::on_toCalculate_clicked() {
        //Считаем значение из первого lineEdit
        QString str_HuT = ui->lineEdit_HuT->text();
        //Переведем значение в число
        calcThermIndicators.HuT = str_HuT.toInt();

        QString str_m1 = ui->lineEdit_m_1->text();
        calcThermIndicators.m1 = str_m1.toDouble();

        QString str_i = ui->lineEdit_i->text();
        calcThermIndicators.numCylinders = str_i.toInt();

        QString str_D = ui->lineEdit_D->text();
        calcThermIndicators.cylDiam = str_D.toDouble();

        QString str_Fn = ui->lineEdit_Fn->text();
        calcThermIndicators.areaPist = str_Fn.toDouble();

        QString str_rk = ui->lineEdit_rk->text();
        calcThermIndicators.crankRad = str_rk.toDouble();

        QString str_lambda_k = ui->lineEdit_lambda_k->text();
        calcThermIndicators.lambda = str_lambda_k.toDouble();

        QString str_Fnn = ui->lineEdit_Fnn->text();
        calcThermIndicators.areaExPist = str_Fnn.toDouble();

        QString str_Fk = ui->lineEdit_Fk->text();
        calcThermIndicators.areaExCap = str_Fk.toDouble();

        QString str_Vc = ui->lineEdit_Vc->text();
        calcThermIndicators.Vc = str_Vc.toDouble();

        QString str_Pk = ui->lineEdit_Pk->text();
        calcThermIndicators.Pk = str_Pk.toDouble();

        QString str_Tk = ui->lineEdit_Tk->text();
        calcThermIndicators.Tk = str_Tk.toDouble();

        QString str_fic = ui->lineEdit_fic->text();
        calcThermIndicators.fiC = str_fic.toInt();

        QString str_fiz = ui->lineEdit_fiz->text();
        calcThermIndicators.fiZ = str_fiz.toInt();

        QString str_omega = ui->lineEdit_w->text();
        calcThermIndicators.omega = str_omega.toDouble();

        QString str_a = ui->lineEdit_a->text();
        calcThermIndicators.alpha = str_a.toDouble();

        QString str_mtc = ui->lineEdit_mtc->text();
        calcThermIndicators.cyclFuel = str_mtc.toDouble();

        QString str_Tw = ui->lineEdit_Tw->text();
        calcThermIndicators.Tw = str_Tw.toDouble();

        QString str_Pa = ui->lineEdit_Pa->text();
        calcThermIndicators.Pa = str_Pa.toDouble();

        QString str_Ta = ui->lineEdit_Ta->text();
        calcThermIndicators.Ta = str_Ta.toDouble();

        QString str_ma = ui->lineEdit_ma->text();
        calcThermIndicators.ma = str_ma.toDouble();

        QString str_Va = ui->lineEdit_Va->text();
        calcThermIndicators.Va = str_Va.toDouble();

        QString str_mA = ui->lineEdit_mA->text();
        calcThermIndicators.mass = str_mA.toDouble();

        calcThermIndicators.calc();
        add_toTableView();

        if (!calcThermIndicators.array_P.isEmpty()) {
            ui->build_graphic->setEnabled(true);
        }
}

void MainWindow::add_toTableView() {
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    //Заголовки столбцов
            QStringList horizontalHeader;
            horizontalHeader.append("fi");
            horizontalHeader.append("P");
            horizontalHeader.append("T");
            horizontalHeader.append("m");
            horizontalHeader.append("V");
            horizontalHeader.append("alphaW");
            horizontalHeader.append("FteplSum");
            horizontalHeader.append("dV");
            horizontalHeader.append("dQw");
            horizontalHeader.append("dx");
            horizontalHeader.append("dQc");
            horizontalHeader.append("dm");
            horizontalHeader.append("dT");
            horizontalHeader.append("P2");
            horizontalHeader.append("L1");
            horizontalHeader.append("Li");

            model->setHorizontalHeaderLabels(horizontalHeader);

            if(engineCycle == "twoStrokeEngine") {
                startCycle = 180;
                endCycle = 540;
                tableLine = 360;
            } else if(engineCycle == "fourStrokeEngine") {
                startCycle = 0;
                endCycle = 720;
                tableLine = endCycle;
            }

            int step = step_printTable();

//            for (int i = startCycle, lineInTable = 0, fi = 0;
//                 i <= endCycle, lineInTable <= tableLine / step, fi <= tableLine; i += step, lineInTable++, fi += step)

            for (int i = startCycle, lineInTable = 0, fi = 0; fi <= tableLine; i += step, lineInTable++, fi += step) {
                item = new QStandardItem(QString::number(fi));
                model->setItem(lineInTable, 0, item);

                item = new QStandardItem(QString::number(calcThermIndicators.array_P[i], 'f'));
                model->setItem(lineInTable, 1, item);
                //Temporary solution
                QString text = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text);

                item = new QStandardItem(QString::number(calcThermIndicators.array_T[i], 'f'));
                model->setItem(lineInTable, 2, item);
                //Temporary solution
                QString text1 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text1);

                item = new QStandardItem(QString::number(calcThermIndicators.array_m[i], 'f'));
                model->setItem(lineInTable, 3, item);
                //Temporary solution
                QString text2 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text2);

                item = new QStandardItem(QString::number(calcThermIndicators.array_V[i], 'e'));
                model->setItem(lineInTable, 4, item);
                //Temporary solution
                QString text3 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text3);

                item = new QStandardItem(QString::number(calcThermIndicators.array_alphaW[i], 'f'));
                model->setItem(lineInTable, 5, item);
                //Temporary solution
                QString text4 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text4);

                item = new QStandardItem(QString::number(calcThermIndicators.array_FteplSum[i], 'f'));
                model->setItem(lineInTable, 6, item);
                //Temporary solution
                QString text5 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text5);

                item = new QStandardItem(QString::number(calcThermIndicators.array_dV[i], 'e'));
                model->setItem(lineInTable, 7, item);
                //Temporary solution
                QString text6 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text6);

                item = new QStandardItem(QString::number(calcThermIndicators.array_dQw[i], 'f'));
                model->setItem(lineInTable, 8, item);
                //Temporary solution
                QString text7 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text7);

                item = new QStandardItem(QString::number(calcThermIndicators.array_dx[i], 'f'));
                model->setItem(lineInTable, 9, item);
                //Temporary solution
                QString text8 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text8);

                item = new QStandardItem(QString::number(calcThermIndicators.array_dQc[i], 'f'));
                model->setItem(lineInTable, 10, item);
                //Temporary solution
                QString text9 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text9);

                item = new QStandardItem(QString::number(calcThermIndicators.array_dm[i], 'f'));
                model->setItem(lineInTable, 11, item);
                //Temporary solution
                QString text10 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text10);

                item = new QStandardItem(QString::number(calcThermIndicators.array_dT[i], 'f'));
                model->setItem(lineInTable, 12, item);
                //Temporary solution
                QString text11 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text11);

                item = new QStandardItem(QString::number(calcThermIndicators.array_P2[i], 'f'));
                model->setItem(lineInTable, 13, item);
                //Temporary solution
                QString text12 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text12);

                item = new QStandardItem(QString::number(calcThermIndicators.array_L1[i], 'e'));
                model->setItem(lineInTable, 14, item);
                //Temporary solution
                QString text13 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text13);

                item = new QStandardItem(QString::number(calcThermIndicators.array_Li[i], 'e'));
                model->setItem(lineInTable, 15, item);
                //Temporary solution
                QString text14 = item->text().replace(".", ",", Qt::CaseSensitive);
                item->setText(text14);
            }

            item = new QStandardItem(QString(""));
            model->setItem(tableLine / step + 3, 1, item);
            item->setText(ui->lineEdit_name->text());

            item = new QStandardItem(QString(""));
            model->setItem(tableLine / step + 4, 1, item);
            item->setText("Дата:" + QDate::currentDate().toString("dd.MM.yyyy"));

            //Li
            item = new QStandardItem(QString::number(calcThermIndicators.array_Li[720], 'f'));
            model->setItem(tableLine / step + 5, 1, item);
            //Temporary solution
            QString textLi = item->text().replace(".", ",", Qt::CaseSensitive);
            item->setText("Li = " + textLi + " Дж/цикл");

            //pi
            item = new QStandardItem(QString::number(calcThermIndicators.pi, 'f'));
            model->setItem(tableLine / step + 6, 1, item);
            //Temporary solution
            QString textPi = item->text().replace(".", ",", Qt::CaseSensitive);
            item->setText("pi = " + textPi + " Па");

            //KKDi
            item = new QStandardItem(QString::number(calcThermIndicators.KKDi, 'f'));
            model->setItem(tableLine / step + 7, 1, item);
            //Temporary solution
            QString textKKDi = item->text().replace(".", ",", Qt::CaseSensitive);
            item->setText("KKDi = " + textKKDi);

            //gi
            item = new QStandardItem(QString::number(calcThermIndicators.gi, 'f'));
            model->setItem(tableLine / step + 8, 1, item);
            //Temporary solution
            QString textGi = item->text().replace(".", ",", Qt::CaseSensitive);
            item->setText("gi = " + textGi + " кг/(кВт*год)");

            ui->tableView->setModel(model);

            ui->tableView->resizeRowsToContents();
            ui->tableView->resizeColumnsToContents();

            //hide defoult vertical tabel
            ui->tableView->verticalHeader()->setVisible(false);
}

int MainWindow::step_printTable() {
    //Считаем значение из первого lineEdit
    QString str_step = ui->lineEdit_step->text();
    qDebug("step = %d", str_step.toInt());
    if(str_step.toInt() < 1) {
        return 1;
    } else {
        return str_step.toInt();
    }
}

void MainWindow::on_saveAsCSV_clicked() {
    QString filename = QFileDialog::getSaveFileName(this,
                                                   tr("Save csv"), ".",
                                                   tr("csv files (*.csv)"));

    QFile f(filename);

        if( f.open( QIODevice::WriteOnly ) )
        {
            QTextStream ts( &f );
            QStringList strList;

            strList << "\" \"";
            for( int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c)
                strList << "\""+ui->tableView->model()->headerData(c, Qt::Horizontal).toString()+"\"";
            ts << strList.join( ";" )+"\n";

            for( int r = 0; r < ui->tableView->verticalHeader()->count(); ++r )
            {
                strList.clear();
                strList << "\""+ui->tableView->model()->headerData(r, Qt::Vertical).toString()+"\"";
                for( int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c )
                {
                    strList << "\""+ui->tableView->model()->data(ui->tableView->model()->index(r, c), Qt::DisplayRole).toString()+"\"";
                }
                ts << strList.join( ";" )+"\n";
            }
            f.close();
        }
}



void MainWindow::setNewThermophisicalParametersSlot(Fuel newFuelParameters) {
    calcThermIndicators.fuel.Cv  = newFuelParameters.Cv;
    calcThermIndicators.fuel.Cp  = newFuelParameters.Cp;
    calcThermIndicators.fuel.Cvg = newFuelParameters.Cvg;
    calcThermIndicators.fuel.Cpg = newFuelParameters.Cpg;
    calcThermIndicators.fuel.k   = newFuelParameters.k;
    calcThermIndicators.fuel.kg  = newFuelParameters.kg;
    calcThermIndicators.fuel.L0  = newFuelParameters.L0;
}

void MainWindow::on_radioButton_4StrokeEngine_clicked() {
    engineCycle = "fourStrokeEngine";
}

void MainWindow::on_radioButton_2StrokeEngine_clicked() {
    engineCycle = "twoStrokeEngine";
}

void MainWindow::on_radioButton_In_lineEngine_clicked() {
    configEng = "In_lineEngine";
}

void MainWindow::on_radioButton_V_shaped_clicked() {
    configEng = "V_shaped";
}

void MainWindow::on_savaToDB_clicked()
{
    EngineParameters engParam;
    engParam.id = engineArray.count();
    engParam.name_Engine = ui->lineEdit_name->text();
    engParam.strokeEngine = engineCycle;
    engParam.configureEngine = configEng;
    engParam.HuT = ui->lineEdit_HuT->text().toInt();
    engParam.m1 = ui->lineEdit_m_1->text().toDouble();
    engParam.i = ui->lineEdit_i->text().toDouble();
    engParam.D = ui->lineEdit_D->text().toDouble();
    engParam.Fn = ui->lineEdit_Fn->text().toDouble();
    engParam.rk = ui->lineEdit_rk->text().toDouble();
    engParam.lambda = ui->lineEdit_lambda_k->text().toDouble();
    engParam.Fnn = ui->lineEdit_Fnn->text().toDouble();
    engParam.Fk = ui->lineEdit_Fk->text().toDouble();
    engParam.Vc = ui->lineEdit_Vc->text().toDouble();
    engParam.Pk = ui->lineEdit_Pk->text().toDouble();
    engParam.Tk = ui->lineEdit_Tk->text().toDouble();
    engParam.fiC = ui->lineEdit_fic->text().toInt();
    engParam.fiZ = ui->lineEdit_fiz->text().toInt();
    engParam.omega = ui->lineEdit_w->text().toDouble();
    engParam.a = ui->lineEdit_a->text().toDouble();
    engParam.mtc = ui->lineEdit_mtc->text().toDouble();
    engParam.Tw = ui->lineEdit_Tw->text().toDouble();
    engParam.Pa = ui->lineEdit_Pa->text().toDouble();
    engParam.Ta = ui->lineEdit_Ta->text().toDouble();
    engParam.ma = ui->lineEdit_ma->text().toDouble();
    engParam.Va = ui->lineEdit_Va->text().toDouble();
    engParam.m_A = ui->lineEdit_mA->text().toDouble();
    engParam.mKKD = ui->lineEdit_KKD->text().toDouble();
    engParam.Cv = calcThermIndicators.fuel.Cv;
    engParam.Cp = calcThermIndicators.fuel.Cp;
    engParam.k = calcThermIndicators.fuel.k;
    engParam.Cvg = calcThermIndicators.fuel.Cvg;
    engParam.Cpg = calcThermIndicators.fuel.Cpg;
    engParam.kg = calcThermIndicators.fuel.kg;
    engParam.L0 = calcThermIndicators.fuel.L0;

    database.saveParametersEngine(&engParam);
    engineArray = database.getEngineParameters();
    reloadDataWidgetList(engineArray);
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index) {
    selectIndex = index.row();

    EngineParameters engPrmt = engineArray[index.row()];
    ui->detailBox->setTitle(engPrmt.name_Engine);
    ui->label_Cv->setText(QString().number(engPrmt.Cv));
    ui->label_Cp->setText(QString().number(engPrmt.Cp));
    ui->label_Cvg->setText(QString().number(engPrmt.Cvg));
    ui->label_Cpg->setText(QString().number(engPrmt.Cpg));
    ui->label_k->setText(QString().number(engPrmt.k));
    ui->label_kg->setText(QString().number(engPrmt.kg));
    ui->label_L0->setText(QString().number(engPrmt.L0));

    ui->label_Hut->setText(QString().number(engPrmt.HuT));
    ui->label_m1->setText(QString().number(engPrmt.m1));
    ui->label_i->setText(QString().number(engPrmt.i));
    ui->label_D->setText(QString().number(engPrmt.D));
    ui->label_Fn->setText(QString().number(engPrmt.Fn));
    ui->label_rk->setText(QString().number(engPrmt.rk));
    ui->label_lambda->setText(QString().number(engPrmt.lambda));
    ui->label_Fnn->setText(QString().number(engPrmt.Fnn));
    ui->label_Fk->setText(QString().number(engPrmt.Fk));
    ui->label_Vc->setText(QString().number(engPrmt.Vc));
    ui->label_Pk->setText(QString().number(engPrmt.Pk));
    ui->label_Tk->setText(QString().number(engPrmt.Tk));
    ui->label_fic->setText(QString().number(engPrmt.fiC));
    ui->label_fiz->setText(QString().number(engPrmt.fiZ));
    ui->label_w->setText(QString().number(engPrmt.omega));
    ui->label_a->setText(QString().number(engPrmt.a));
    ui->label_mtc->setText(QString().number(engPrmt.mtc));
    ui->label_Tw->setText(QString().number(engPrmt.Tw));
    ui->label_Pa->setText(QString().number(engPrmt.Pa));
    ui->label_Ta->setText(QString().number(engPrmt.Ta));
    ui->label_ma->setText(QString().number(engPrmt.ma));
    ui->label_Va->setText(QString().number(engPrmt.Va));
    ui->label_mA->setText(QString().number(engPrmt.m_A));
    ui->label_kkd->setText(QString().number(engPrmt.mKKD));

    if (engPrmt.Cv == 727.6 && engPrmt.Cp == 1014.6 && engPrmt.Cvg == 954.1 && engPrmt.Cpg == 1241.1 && engPrmt.k == 1.4 && engPrmt.kg == 1.3 && engPrmt.L0 == 0.516) {
        //petrol
        ui->furl_groupBox->setTitle("Паливо - бензин");
    } else if (engPrmt.Cv == 740.5 && engPrmt.Cp == 1027.5 && engPrmt.Cvg == 905.5 && engPrmt.Cpg == 1192.5 && engPrmt.k == 1.39 && engPrmt.kg == 1.32 && engPrmt.L0 == 0.500) {
        //disel
        ui->furl_groupBox->setTitle("Паливо - дизельне");
    } else{
        ui->furl_groupBox->setTitle("Паливо - інше");
    }


    if (engPrmt.strokeEngine == "fourStrokeEngine") {
        ui->label_stroke->setText("4 - тактний");
    } else  {
        ui->label_stroke->setText("2 - тактний");
    }

    if (engPrmt.configureEngine == "In_lineEngine") {
        ui->label_config->setText("Рядний");
    } else {
        ui->label_config->setText("V-подібний");
    }
}

void MainWindow::on_pushButton_deleteEngine_clicked() {
    database.deleteParameters(engineArray[selectIndex].id, "engine");
    engineArray = database.getEngineParameters();
    reloadDataWidgetList(engineArray);
}

void MainWindow::on_pushButton_loadEngine_clicked()
{
    EngineParameters *load = &engineArray[selectIndex];
    ui->lineEdit_name->setText(load->name_Engine);
    ui->lineEdit_HuT->setText(QString().number(load->HuT));
    ui->lineEdit_m_1->setText(QString().number(load->m1));
    ui->lineEdit_i->setText(QString().number(load->i));
    ui->lineEdit_D->setText(QString().number(load->D));
    ui->lineEdit_Fn->setText(QString().number(load->Fn));
    ui->lineEdit_rk->setText(QString().number(load->rk));
    ui->lineEdit_lambda_k->setText(QString().number(load->lambda));
    ui->lineEdit_Fnn->setText(QString().number(load->Fnn));
    ui->lineEdit_Fk->setText(QString().number(load->Fk));
    ui->lineEdit_Vc->setText(QString().number(load->Vc));
    ui->lineEdit_Pk->setText(QString().number(load->Pk));
    ui->lineEdit_Tk->setText(QString().number(load->Tk));
    ui->lineEdit_fic->setText(QString().number(load->fiC));
    ui->lineEdit_fiz->setText(QString().number(load->fiZ));
    ui->lineEdit_w->setText(QString().number(load->omega));
    ui->lineEdit_a->setText(QString().number(load->a));
    ui->lineEdit_mtc->setText(QString().number(load->mtc));
    ui->lineEdit_Tw->setText(QString().number(load->Tw));
    ui->lineEdit_Pa->setText(QString().number(load->Pa));
    ui->lineEdit_Ta->setText(QString().number(load->Ta));
    ui->lineEdit_ma->setText(QString().number(load->ma));
    ui->lineEdit_Va->setText(QString().number(load->Va));
    ui->lineEdit_mA->setText(QString().number(load->m_A));
    ui->lineEdit_KKD->setText(QString().number(load->mKKD));
    on_radioButton_Petrol_clicked();
    //add radiobutton
    if (load->Cv == 727.6 && load->Cp == 1014.6 && load->Cvg == 954.1 && load->Cpg == 1241.1 && load->k == 1.4 && load->kg == 1.3 && load->L0 == 0.516) {
        on_radioButton_Petrol_clicked();
        ui->radioButton_Petrol->click();
    } else if (load->Cv == 740.5 && load->Cp == 1027.5 && load->Cvg == 905.5 && load->Cpg == 1192.5 && load->k == 1.39 && load->kg == 1.32 && load->L0 == 0.500) {
        on_radioButton_Diesel_clicked();
        ui->radioButton_Diesel->click();
    } else {
        on_radioButton_Other_clicked();
        ui->radioButton_Other->click();
    }

    if (load->strokeEngine == "fourStrokeEngine") {
        on_radioButton_4StrokeEngine_clicked();
        ui->radioButton_4StrokeEngine->click();
    } else if (load->strokeEngine == "twoStrokeEngine") {
        on_radioButton_2StrokeEngine_clicked();
        ui->radioButton_2StrokeEngine->click();
    }

    if (load->configureEngine == "In_lineEngine") {
        on_radioButton_In_lineEngine_clicked();
        ui->radioButton_In_lineEngine->click();
    } else if (load->configureEngine == "V_shaped") {
        on_radioButton_V_shaped_clicked();
        ui->radioButton_V_shaped->click();
    }
}

void MainWindow::on_radioButton_Other_clicked() {
    //send param
}

void MainWindow::on_thermoPhishicButton_clicked() {
    emit getDBManegerSignal(&database);

    if(!_thermophysicalParameters) {
        _thermophysicalParameters = new ThermophysicalParameters(this);
        connect(_thermophysicalParameters, &ThermophysicalParameters::setNewThermophisicalParametersSignal, this, &MainWindow::setNewThermophisicalParametersSlot);
        connect(this, &MainWindow::getDBManegerSignal, _thermophysicalParameters, &ThermophysicalParameters::setDBManegerSlot);
    }

    _thermophysicalParameters->show();
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == 4 && calcThermIndicators.array_P.isEmpty()) {
        ui->build_graphic->setEnabled(false);
    }
}

//void MainWindow::on_build_graphic_clicked() {

//    //emit setThermIndSignal(9);
//    BuildGraphic buildgraphic;
//    //if(!buildgraphic) {
//      //  buildgraphic = new BuildGraphic(this);
//    //}
//    buildgraphic.t = 6;

//    buildgraphic->tIndicatorsArray.append(ThermInd("P", &calcThermIndicators.array_P));
//    buildgraphic->tIndicatorsArray.append(ThermInd("T", &calcThermIndicators.array_T));
//    buildgraphic->tIndicatorsArray.append(ThermInd("m", &calcThermIndicators.array_m));
//    buildgraphic->tIndicatorsArray.append(ThermInd("V", &calcThermIndicators.array_V));
//    buildgraphic->tIndicatorsArray.append(ThermInd("alphaW", &calcThermIndicators.array_alphaW));
//    buildgraphic->tIndicatorsArray.append(ThermInd("FteplSum", &calcThermIndicators.array_FteplSum));
//    buildgraphic->tIndicatorsArray.append(ThermInd("dV", &calcThermIndicators.array_dV));
//    buildgraphic->tIndicatorsArray.append(ThermInd("dQw", &calcThermIndicators.array_dQw));
//    buildgraphic->tIndicatorsArray.append(ThermInd("dQc", &calcThermIndicators.array_dQc));
//    buildgraphic->tIndicatorsArray.append(ThermInd("dx", &calcThermIndicators.array_dx));
//    buildgraphic->tIndicatorsArray.append(ThermInd("dm", &calcThermIndicators.array_dm));
//    buildgraphic->tIndicatorsArray.append(ThermInd("dT", &calcThermIndicators.array_dT));
//    buildgraphic->tIndicatorsArray.append(ThermInd("P2", &calcThermIndicators.array_P2));
//    buildgraphic->tIndicatorsArray.append(ThermInd("L1", &calcThermIndicators.array_L1));
//    buildgraphic->tIndicatorsArray.append(ThermInd("Li", &calcThermIndicators.array_Li));

//    //connect(this, &MainWindow::setThermIndSignal, &bgw, &BuildGraphWindow::thermIndSlot);
//    buildgraphic.setModal(true);
//    buildgraphic.exec();
//}

void MainWindow::on_build_graphic_clicked() {
    BuildGraphWindow bgw;


}
