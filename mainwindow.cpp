#include "mainwindow.h"
#include "ui_mainwindow.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ini set
    lv_state = false;
    run_state = false;
    speed_cmd = 0;
    ui->btnRun->setEnabled(false);
    chartindex = 0;

    // QtreeWidget
    QStringList Speeditem;
    Speeditem << "---Speed---";
    item1 = new QTreeWidgetItem(ui->treeWidget,Speeditem);
    item1->setIcon(0,QIcon(":/signal_red.png"));
    item1->setText(1,"aaaa");
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    // QTimer setting
    paintInterv = new QTimer;
    paintInterv->stop();
    paintInterv->setInterval(500);
    paintInterv->start();

    //QChart set
    chart1 = new QChart;
    axisX = new QValueAxis;
    axisY = new QValueAxis;
    axisX->setRange(0,200);
    axisY->setRange(0,200);
    lineseries = new QLineSeries;
    lineseries->setName("line1");
    chart1->addAxis(axisX,Qt::AlignBottom);
    chart1->addAxis(axisY,Qt::AlignLeft);
    chart1->addSeries(lineseries);
    chart1->setTitle("test for it");
    ui->QChatView_1->setChart(chart1);
    ui->QChatView_1->setRubberBand(QChartView::RectangleRubberBand);
    ui->QChatView_1->setRenderHint(QPainter::Antialiasing);
    lineseries->attachAxis(axisX);
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
       chartindex++;
       ui->speedLcd->display(speed_cmd);
       ui->spinSpeed->setValue(speed_cmd);
       lineseries->append(chartindex,speed_cmd);
       item1->setText(1,QString::number(speed_cmd,10,2));

       if (speed_cmd > 200 || chartindex >200)
       {
           axisX->setRange(0,chartindex);
           axisY->setRange(0,speed_cmd);
       }
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
