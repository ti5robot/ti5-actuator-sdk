#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtCharts>
#include <QTimer>
#include <QTime>
#include <QChart>
#include "actuator_control_interface.h"
#include "dialognotice.h"
#include "server.h"
extern int route[200];
extern int route1[1001];
extern int route2[1001];
extern int route3[1001];
extern int route4[1001];
extern int route5[1001];
extern int route6[1001];

extern int numnum123;

namespace Ui {
class MainWindow;
}
#define ROUTE_SIZE 200
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int r1[10000]={0};
    int r2[10000]={0};
    int r3[10000]={0};
    int r4[10000]={0};
    int r5[10000]={0};
    int r6[10000]={0};
    bool serialPortConnect = false;
    Actuator_Control_interface ACI;
    QTimer uiTimer;
    Serial comPort;
    UFCP ufcp;
    char * serialportName = "com4";

    //波形图
    QChart* chart;
//    PlotData_t plotData;
    QLineSeries plotCurrent;
    QLineSeries plotSpeed;
    QLineSeries plotPosition;
    QLineSeries plotTargetCurrent;
    QLineSeries plotTargetSpeed;
    QLineSeries plotTargetPosition;
    QValueAxis axisBasex;
    QValueAxis axisyS16;
    QValueAxis axisyS32;
    QValueAxis axisy2;
    QValueAxis axisy3;
    void sleep(unsigned int msec);
    void qt_write_csv_test(int aa);
private slots:

    void elapsed_time();


    void on_pushButton_findActuator_released();

    void on_pushButtonTCP_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
