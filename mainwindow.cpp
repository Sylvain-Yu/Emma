#include "mainwindow.h"
#include "ui_mainwindow.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ini set
    speed_cmd = 0;
    ui->btnRun->setEnabled(false);

    // QtreeWidget
    QStringList Speeditem;
    Speeditem << "<Speed>";
    Speeditem << "sss";
    item1 = new QTreeWidgetItem(ui->treeWidget,Speeditem);
    item1->setIcon(0,QIcon(":/signal_red.png"));
    item1->addChildren(
//    item1->setText(1,"None");
    auto item2 = new QTreeWidgetItem(item1,Speeditem);
    item2->setText(1,"abc");

    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // QTimer setting
    paintInterv = new QTimer;
    paintInterv->stop();
    paintInterv->setInterval(500);
    paintInterv->start();

    //QChart set
    chart1 = new QChart;
    axisDatatimeX = new QDateTimeAxis;
    axisDatatimeX->setFormat("ss:zz");
    now = QDateTime::currentDateTime();
    axisDatatimeX->setRange(now.addSecs(-200),now.addSecs(200));
    axisDatatimeX->setTickCount(5);


    axisY = new QValueAxis;
    lineseries = new QLineSeries;
    lineseries->setName("line1");
    chart1->addAxis(axisDatatimeX,Qt::AlignBottom);
    chart1->addAxis(axisY,Qt::AlignLeft);
    chart1->addSeries(lineseries);
    chart1->setTitle("test for it");
    ui->QChatView_1->setChart(chart1);
    ui->QChatView_1->setRubberBand(QChartView::RectangleRubberBand);
    ui->QChatView_1->setRenderHint(QPainter::Antialiasing);
    lineseries->attachAxis(axisDatatimeX);
    lineseries->attachAxis(axisY);

    // signal -> slot
    connect(paintInterv,SIGNAL(timeout()),this,SLOT(paintInter_timeout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintInter_timeout()
{
   if (run_state&&lv_state)
   {
       speed_cmd++;
       now = QDateTime::currentDateTime();
       ui->speedLcd->display(speed_cmd);
       ui->spinSpeed->setValue(speed_cmd);
       lineseries->append( now.toMSecsSinceEpoch(),speed_cmd);
       item1->setText(1,QString::number(speed_cmd,10,2));
       axisY->setRange(0,speed_cmd+10);
  }
}

void MainWindow::on_btnRun_clicked(bool checked)
{
    if (checked)
    {
        run_state = true;
        ui->btnRun->setText(STOP_ID);
    }
    else {
        run_state = false;
        ui->btnRun->setText(RUN_ID);
    }
}

void MainWindow::on_btnLv_clicked(bool checked)
{
    if (checked)
    {
        lv_state = true;
        ui->btnLv->setText("Lv Disable");
        ui->btnRun->setEnabled(true);
    }
    else {
        lv_state = false;
        run_state = false;
        ui->btnLv->setText("Lv Enable");
        ui->btnRun->setEnabled(false);
        ui->btnRun->setChecked(false);
        ui->btnRun->setText(RUN_ID);
        ui->spinSpeed->setValue(0);
        ui->spinTorque->setValue(0);
    }
}


void MainWindow::on_spinSpeed_valueChanged(int arg1)
{
   speed_cmd = arg1;
   if (run_state && lv_state)
   {
       ui->speedLcd->display(speed_cmd);
   }
   else {
       ui->speedLcd->display(0);
       ui->spinSpeed->setValue(0);
   }
}

void MainWindow::on_spinTorque_valueChanged(int arg1)
{
   torque_cmd = arg1;
   if (run_state && lv_state)
   {
       ui->torqueLcd->display(torque_cmd);
   }
   else {
       ui->torqueLcd->display(0);
       ui->spinTorque->setValue(0);
   }
}

void MainWindow::on_btnLog_clicked(bool checked)
{
    if (checked)
    {
        QString savefile = QFileDialog::getSaveFileName(this,QStringLiteral("Save"),"","txt(*.txt);;csv(*.csv)");
        qDebug()<< savefile;
        QFile afile(savefile);
        if (afile.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QTextStream aStream(&afile);
            aStream << "helloworld,nice\nto,meet,you!";
            afile.close();
        }
    }
}
