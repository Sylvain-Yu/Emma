#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QTreeWidgetItem>
#include <QtCharts>
#define STOP_ID "STOP"
#define RUN_ID "RUN"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnRun_clicked(bool checked);

    void on_btnLv_clicked(bool checked);

    void on_spinTorque_valueChanged(int arg1);

    void on_spinSpeed_valueChanged(int arg1);

    void paintInter_timeout();

private:
    Ui::MainWindow *ui;
    int speed_cmd;
    int torque_cmd;
    bool run_state;
    bool lv_state;
    QTimer *paintInterv;
    QLineSeries *lineseries;
    QChart * chart1;
    int chartindex;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QTreeWidgetItem *item1;

};
#endif // MAINWINDOW_H
