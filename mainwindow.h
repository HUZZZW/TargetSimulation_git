#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QFile>
#include <QMessageBox>
#include <QFile>
#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>
#include <iterator>
#include <QDir>
#include <cmath>
#include <QThread>
#include <QMainWindow>
#include <QFileDialog>
#include <QJsonParseError>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonArray>
#include "qtudpcom.h"
#include "model/config.h"
#include "model/Usp.h"
#include "model/FcowMsg.h"
#include "addnewtarget.h"
#include "checkresults.h"
#include <QJsonObject>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    QtUdpCom* udpCom=new QtUdpCom(this);
    QUdpSocket* udpSocket_;
    QHostAddress groupAddress;
//***********************************************************
//***********************************************************

//添加表格项目***********************************************************
public slots:
    void SaveDroneTable();//往表格里添加项目
    void RemoveDroneTable();//删除表格里的项目
public:
    int deleteindex;
    QVector<QStringList> dataSet;
    QVector<AddNewTarget*> Muti_thread;
    int dataSetNum;
    QStringList strList;
    double distence,x,x_simu,y,y_simu,z,z_simu,xy,xy_simu,pit,rate;
//***********************************************************************
//添加检测结果*************************************************************
public slots:
    void SaveChkReslutsTable();
    void RemoveChkReslutsTable();
public:
    int deleteindex_ChkRe;
    QVector<QStringList>dataSet_ChkRe;
    QVector<CheckResults*>Muti_thread_ChkRe;
    int dataSetNum_ChkRe;
    QStringList strList_ChkRe;
    CheckResults *CheckResults_=new CheckResults;
//***********************************************************************


//飞行控制****************************************************************
/*松刹车*/
public slots:
    void send_release_break();
public:
    schedule::FcowDroneArmPara *FcowDroneArmPara_;
/*刹车*/
public slots:
    void send_break();
public:
    schedule::FcowDroneDisarmPara *FcowDroneDisarmPara_;
/*起飞*/
public slots:
    void send_departure();
public:
    schedule::FcowDroneTakeoffPara* FcowDroneTakeoffPara_;
/*返航*/
public slots:
    void send_GoBackPara();
public:
    schedule::FcowDroneGoBackPara* FcowDroneGoBackPara_;
/*发送航线*/
public slots:
    void send_AirRoute();
public:
    schedule::FcowDroneNewRoutePara* FcowDroneNewRoutePara_ = new schedule::FcowDroneNewRoutePara;
    vector<schedule::FlyPoint*> *FlyPoint_Vector;
    schedule::FcowDroneRoute* FcowDroneRoute_;
    schedule::FlyPoint* FlyPoint_;
    vector<schedule::CameraPreset*>* CameraPreset_vector;
    schedule::CameraPreset* CameraPreset_;
    bool ifclicked=false;
/*执行航线*/
public slots:
    void send_ExeAirRoute();
public:
    schedule::FcowDroneGoRoutePara* FcowDroneGoRoutePara_;
    int routeId_Num=1;
//***********************************************************************


//吊舱控制****************************************************************
public:
    schedule::UavGimbalCtrlPara* UavGimbalCtrlPara_ = new schedule::UavGimbalCtrlPara;
/*上*/
public slots:
    void send_GimbalCtrl_Up();
/*下*/
public slots:
    void send_GimbalCtrl_Down();
/*左*/
public slots:
    void send_GimbalCtrl_left();
/*右*/
public slots:
    void send_GimbalCtrl_right();
/*焦距+*/
public slots:
    void send_GimbalCtrl_Focal_Plus();
/*焦距-*/
public slots:
    void send_GimbalCtrl_Focal_Reduce();
/*拍照一张*/
public slots:
    void send_GimbalCtrl_Photo();
/*录像开始*/
public slots:
    void send_GimbalCtrl_Record_Start();
/*录像结束*/
public slots:
    void send_GimbalCtrl_Record_End();
//***********************************************************************
//雷达控制****************************************************************
public:
    schedule::UavRadarCtrlPara* UavRadarCtrlPara_ = new schedule::UavRadarCtrlPara;
public slots:
    void send_RadarCtrlPara_Scan_Scope();
    void send_RadarCtrlPara_Scan_Speed();


//***********************************************************************
private slots:
    void on_checkBox_clicked(bool checked);
    void on_pushButton_3_clicked();
    void on_pushButton_12_clicked();
};

#endif // MAINWINDOW_H
