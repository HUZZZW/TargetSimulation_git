#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addnewtarget.h"
//添加目标************************************************************************************************
void MainWindow::SaveDroneTable()
{
    if (ui->TargetIDT1->text() !="" && ui->Str_lng->text()!="" && ui->Str_lat->text()!="" && ui->Str_alt->text()!="" && ui->End_lng->text()!="" && ui->End_lat->text()!="" && ui->End_alt->text()!="")
    {
        if(ui->Str_lng->text().toFloat()<=180.0 && ui->Str_lng->text().toFloat()>=-180.0 && ui->Str_lat->text().toFloat()<=90.0 && ui->Str_lat->text().toFloat()>=-90.0 &&
           ui->End_lng->text().toFloat()<=180.0 && ui->End_lng->text().toFloat()>=-180.0 && ui->End_lat->text().toFloat()<=90.0 && ui->End_lat->text().toFloat()>=-90.0)
        {
            bool ifrepet=false;//检查输入代码是否重复
            int repetLine=0;
            for(int i=0;i<dataSet.size();i++)//检查每个vector的目标标识
            {
                if(ui->TargetIDT1->text()==dataSet[i][0])//如果目标标识重复的话进行记录，并且记录是第几行重复的
                {
                    ifrepet=true;
                    repetLine=i;
                    break;
                }
                else
                {//如果没有重复的目标标识回复false
                    ifrepet=false;
                }
            }
            AddNewTarget *AddNewTarget_ = new AddNewTarget;
            if(!ifrepet)//如果输入目标标识不重复则在表格最后添加一行
            {
                ui->tableWidget->setRowCount(dataSetNum+1);
                strList[0]= ui->TargetIDT1->text();//添加目标标识
                strList[1]= ui->comboBox->currentText() ;//添加目标类型
                strList[2]= ui->Str_lng->text();//添加起始经度
                strList[3]= ui->Str_lat->text();//添加起始纬度
                strList[4]= ui->Str_alt->text();//添加起始高度
                strList[5]= ui->End_lng->text();//添加结束经度
                strList[6]= ui->End_lat->text();//添加结束纬度
                strList[7]= ui->End_alt->text();//添加结束高度
                //********************************
                if(ui->checkBox->isChecked())
                {
                    AddNewTarget_->getAddress(ui->addressBox_all->text());
                    AddNewTarget_->getport(ui->PortBox_all->text().toInt());
                }
                else
                {
                    AddNewTarget_->getAddress(ui->addressBox1->text());
                    AddNewTarget_->getport(ui->PortBox1->text().toInt());
                }
                AddNewTarget_->Flight_Information(strList);
                Muti_thread.push_back(AddNewTarget_);
                //********************************
                dataSet.push_back(strList);//将一行的数据添加到Vector里
                for(int i=0; i<dataSet.size(); i++) {//重新打印列表到UI
                    for (int j=0; j<8; j++) {
                        ui->tableWidget->setItem(i, j, new QTableWidgetItem(dataSet[i][j]));
                    }
                }
                dataSetNum++;
                QApplication::processEvents();
             }
            else//如果输入标识码重复则修改原标识码位置上的函数
            {
                dataSet[repetLine][0]=ui->TargetIDT1->text();//修改vector里的目标标识
                strList[0]= ui->TargetIDT1->text();//更新目标标识

                dataSet[repetLine][1]=ui->comboBox->currentText();//修改vector里的目标类型
                strList[1]= ui->comboBox->currentText() ;//更新目标类型

                dataSet[repetLine][2]=ui->Str_lng->text();//修改vector里的起始经度
                strList[2]= ui->Str_lng->text();//更新起始经度

                dataSet[repetLine][3]=ui->Str_lat->text();//修改vector里的起始纬度
                strList[3]= ui->Str_lat->text();//更新起始纬度


                dataSet[repetLine][4]=ui->Str_alt->text();//修改vector里的起始高度
                strList[4]= ui->Str_alt->text();//更新起始高度

                dataSet[repetLine][5]=ui->End_lng->text();//修改vector里的结束经度
                strList[5]= ui->End_lng->text();//更新结束经度

                dataSet[repetLine][6]=ui->End_lat->text();//修改vector里的结束纬度
                strList[6]= ui->End_lat->text();//更新结束纬度

                dataSet[repetLine][7]=ui->End_alt->text();//修改vector里的结束高度
                strList[7]= ui->End_alt->text();//更新结束高度
                //结束旧线程添加新的线程*******************************************************
                int idx = 0;
                while(1)
                {
                   if(Muti_thread[idx]->Drone_Information->regno == ui->TargetIDT1->text().toStdString())
                   {
                       Muti_thread[idx]->deleteThread();
                       if(ui->checkBox->isChecked())
                       {
                           Muti_thread[idx]->getAddress(ui->addressBox_all->text());
                           Muti_thread[idx]->getport(ui->PortBox_all->text().toInt());
                       }
                       else
                       {
                           Muti_thread[idx]->getAddress(ui->addressBox1->text());
                           Muti_thread[idx]->getport(ui->PortBox1->text().toInt());
                       }
                       Muti_thread[idx]->Flight_Information(strList);
                       break;
                   }
                   idx++;
                }
                for(int i=0; i<dataSet.size(); i++) {
                    for (int j=0; j<8; j++) {
                        ui->tableWidget->setItem(i, j, new QTableWidgetItem(dataSet[i][j]));
                    }
                }
            }
        }
        else{//如果信息没有输入正确则跳出提示框
            QMessageBox::warning(this,"提示","请填写正确经纬度信息",QMessageBox::Ok);
        }
    }
    else{//如果信息没有输入完整则跳出提示框

        QMessageBox::warning(this,"提示","请将信息填写完整",QMessageBox::Ok);
    }
}

void MainWindow::RemoveDroneTable()//删除表格中选中的行数
{
    deleteindex=0;
    QList<QTableWidgetItem*> items=ui->tableWidget->selectedItems();
    int count = items.count();
    if(!items.empty())//判断是否有选中列表中的行，获取选中的行数，如果有选中则进行删除操作
    {
        int finalRow=0;
        int selectItemRow[count];
        for(int i =0;i<count;i++)//将用户选中的表格行数输出到数组里面
       {
            int row =ui->tableWidget->row(items.at(i));
            selectItemRow[i]=row;
            finalRow=row;
       }
        int rest=dataSet.size()-finalRow-1;//读取剩下的行数
        dataSet.erase(dataSet.begin()+selectItemRow[0],dataSet.end()-rest);//删除操作
        //qDebug()<<(selectItemRow[0]);
        deleteindex=selectItemRow[0];
        while(deleteindex<=finalRow)
        {
            Muti_thread[deleteindex]->deleteThread();
            deleteindex+=1;
        }
        Muti_thread.erase(Muti_thread.begin()+selectItemRow[0],Muti_thread.end()-rest);
        //qDebug()<<Muti_thread.begin();
        ui->tableWidget->clearContents();//刷新列表
        for(int i=0; i<dataSet.size(); i++) {//重新打印列表到UI
            for (int j=0; j<8; j++) {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(dataSet[i][j]));
            }
        }
    }
    else
    {
        QMessageBox::warning(this,"警告","请先选择一行再进行操作");
    }

}
//*************************************************************************************************************************
//添加检测结果***************************************************************************************************************
void MainWindow::SaveChkReslutsTable()
{
    if (ui->TargetIDT2->text() !="" && ui->distance1->text() !="" && ui->angle1->text() !="" && ui->addressBox2->text()!="" && ui->PortBox2->text() !="")
    {
        if(ui->angle1->text().toInt() >= 0 && ui->angle1->text().toInt() < 360)
        {
            bool ifrepet=false;//检查输入代码是否重复
            int repetLine=0;
            for(int i=0;i<dataSet_ChkRe.size();i++)//检查每个vector的目标标识
            {
                if(ui->TargetIDT2->text() == dataSet_ChkRe[i][0])//如果目标标识重复的话进行记录，并且记录是第几行重复的
                {
                    ifrepet=true;
                    repetLine=i;
                    break;
                }
                else {//如果没有重复的目标标识回复false
                    ifrepet=false;
                }
            }

            if(!ifrepet)//如果输入目标标识不重复则在表格最后添加一行
            {
                ui->tableWidget_2->setRowCount(dataSetNum_ChkRe+1);
                strList_ChkRe[0]= ui->TargetIDT2->text();//添加目标标识
                strList_ChkRe[1]= ui->distance1->text() ;
                strList_ChkRe[2]= ui->angle1->text();
                //添加线程********************************

                if(ui->checkBox->isChecked())
                {
                    CheckResults_->getAddress(ui->addressBox_all->text());
                    CheckResults_->getport(ui->PortBox_all->text().toInt());
                }
                else
                {
                    CheckResults_->getAddress(ui->addressBox2->text());
                    CheckResults_->getport(ui->PortBox2->text().toInt());
                }
                CheckResults_->checkreslut_information(strList_ChkRe);
                //Muti_thread_ChkRe.push_back(CheckResults_);
                //********************************
                dataSet_ChkRe.push_back(strList_ChkRe);//将一行的数据添加到Vector里
                for(int i=0; i<dataSet_ChkRe.size(); i++) {//重新打印列表到UI
                    for (int j=0; j<dataSet_ChkRe[0].size(); j++) {
                        ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(dataSet_ChkRe[i][j]));
                    }
                }
                dataSetNum_ChkRe++;
                QApplication::processEvents();
            }
            else
            {
                dataSet_ChkRe[repetLine][0] = ui->TargetIDT2->text();
                strList_ChkRe[0] = ui->TargetIDT2->text();
                dataSet_ChkRe[repetLine][1] = ui->distance1->text();
                strList_ChkRe[1] = ui->distance1->text();
                dataSet_ChkRe[repetLine][2] = ui->angle1->text();
                strList_ChkRe[2] = ui->angle1->text();
                //结束旧线程添加新的线程********************************************************
                if(ui->checkBox->isChecked())
                {
                    CheckResults_->getAddress(ui->addressBox_all->text());
                    CheckResults_->getport(ui->PortBox_all->text().toInt());
                }
                else
                {
                    CheckResults_->getAddress(ui->addressBox2->text());
                    CheckResults_->getport(ui->PortBox2->text().toInt());
                }
                CheckResults_->checkreslut_Updata(strList_ChkRe);
                //********************************************************
                for(int i=0; i<dataSet_ChkRe.size(); i++) {//重新打印列表到UI
                    for (int j=0; j<dataSet_ChkRe[0].size(); j++) {
                        ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(dataSet_ChkRe[i][j]));
                    }
                }
            }
        }
        else{
            QMessageBox::warning(this,"提示","请填写正确角度信息",QMessageBox::Ok);
        }
    }
    else{//如果信息没有输入完整则跳出提示框
        QMessageBox::warning(this,"提示","请将信息填写完整",QMessageBox::Ok);
    }

}

void MainWindow::RemoveChkReslutsTable()
{
    deleteindex=0;
    QList<QTableWidgetItem*> items=ui->tableWidget_2->selectedItems();
    int count = items.count();
    if(!items.empty())//判断是否有选中列表中的行，获取选中的行数，如果有选中则进行删除操作
    {
        int finalRow=0;
        int selectItemRow[count];
        for(int i =0;i<count;i++)
       {
            int row =ui->tableWidget_2->row(items.at(i));
            selectItemRow[i]=row;
            finalRow=row;
       }
        int rest=dataSet_ChkRe.size()-finalRow-1;
        dataSet_ChkRe.erase(dataSet_ChkRe.begin()+selectItemRow[0],dataSet_ChkRe.end()-rest);//删除操作
        bool ifclear = true;
        if(dataSet_ChkRe.size()==0)
        {
            ifclear=true;
        }
        else {
            ifclear=false;
        }
        qDebug()<<ifclear;
        CheckResults_->checkreslut_delete(ifclear,selectItemRow[0],rest);
        ui->tableWidget_2->clearContents();//刷新列表
        for(int i=0; i<dataSet_ChkRe.size(); i++) {//重新打印列表到UI
            for (int j=0; j<dataSet_ChkRe[0].size(); j++) {
                ui->tableWidget_2->setItem(i, j, new QTableWidgetItem(dataSet_ChkRe[i][j]));
            }
        }
    }
    else
        {
            QMessageBox::warning(this,"警告","请先选择一行再进行操作");
        }
}
//*************************************************************************************************************************
//飞行控制******************************************************************************************************************
/*松刹车*/
void MainWindow::send_release_break()
{
    FcowDroneArmPara_=new schedule::FcowDroneArmPara;
    if(ui->checkBox->isChecked())
    {
        //udpCom->dataSend(FcowDroneArmPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
        udpSocket_->writeDatagram(FcowDroneArmPara_->toJsonString(),groupAddress,ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(FcowDroneArmPara_->toJsonString(),ui->addressBox3->text(),ui->PortBox3->text().toInt());
    }
}
/*刹车*/
void MainWindow::send_break()
{
    FcowDroneDisarmPara_= new schedule::FcowDroneDisarmPara;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(FcowDroneDisarmPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(FcowDroneDisarmPara_->toJsonString(),ui->addressBox3->text(),ui->PortBox3->text().toInt());
    }
}
/*起飞*/
void MainWindow::send_departure()
{
    FcowDroneTakeoffPara_ = new schedule::FcowDroneTakeoffPara;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(FcowDroneTakeoffPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }

    else
    {
        udpCom->dataSend(FcowDroneTakeoffPara_->toJsonString(),ui->addressBox3->text(),ui->PortBox3->text().toInt());
    }

}
/*返航*/
void MainWindow::send_GoBackPara()
{
    FcowDroneGoBackPara_= new schedule::FcowDroneGoBackPara;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(FcowDroneGoBackPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else
    {
        udpCom->dataSend(FcowDroneGoBackPara_->toJsonString(),ui->addressBox3->text(),ui->PortBox3->text().toInt());
    }
}
/*发送航线*/
void MainWindow::send_AirRoute()
{
    ifclicked=true;
    FcowDroneRoute_=new schedule::FcowDroneRoute;
    QString filename= QFileDialog::getOpenFileName(
                this,
                tr("打开JSON文件。"),
                "*",
                 "*.json"
                );

     //qDebug()<<"print to here!";
     QFile file(filename);
     if(!file.open(QIODevice::ReadWrite))
     {
         qDebug()<<"File open error";
         QMessageBox::warning(this,"警告","未找到目录文件！");
     }
     else {
         qDebug()<<"File open!";
         QByteArray allData = file.readAll();
         file.close();
         QJsonParseError jsonerror;
         QJsonDocument document=QJsonDocument::fromJson(allData,&jsonerror);
         if(jsonerror.error==QJsonParseError::NoError)
         {
            if(document.isObject())
            {
                QJsonObject obj = document.object();
                if(obj.contains("id"))
                {
                     QJsonValue namevalue = obj.value("id");
                     if(namevalue.isString())
                     {

                         FcowDroneRoute_->id = namevalue.toString().toStdString() ;
                     }
                }
                if(obj.contains("name"))
                {
                     QJsonValue namevalue = obj.value("name");
                     if(namevalue.isString())
                     {

                         FcowDroneRoute_->name = namevalue.toString().toStdString() ;
                         //qDebug()<<namevalue.toString();
                     }
                }
                if(obj.contains("pts"))
                {
                     FlyPoint_Vector= new vector<schedule::FlyPoint*>;
                     QJsonValue namevalue = obj.value("pts");
                     if(namevalue.isArray())
                     {

                         QJsonArray temp_arr=namevalue.toArray();
                         for(int i=0;i<temp_arr.size();i++)
                         {
                            FlyPoint_ = new schedule::FlyPoint;
                            QJsonObject obj_pts = temp_arr[i].toObject();

                            QJsonValue ArrayValue = obj_pts.value("name");
                            FlyPoint_->name = ArrayValue.toString().toStdString();

                            ArrayValue = obj_pts.value("alt");
                            FlyPoint_->alt = ArrayValue.toDouble();

                            ArrayValue = obj_pts.value("action");
                            FlyPoint_->action = ArrayValue.toInt();

                            ArrayValue = obj_pts.value("autoCon");
                            FlyPoint_->autoCon = ArrayValue.toInt();

                            ArrayValue = obj_pts.value("cmd");
                            FlyPoint_->cmd = ArrayValue.toInt();

                            ArrayValue = obj_pts.value("flyThr");
                            FlyPoint_->flyThr = ArrayValue.toInt();

                            ArrayValue = obj_pts.value("head");
                            FlyPoint_->head = ArrayValue.toDouble();

                            ArrayValue = obj_pts.value("hov");
                            FlyPoint_->hov=ArrayValue.toInt();

                            ArrayValue = obj_pts.value("hspd");
                            FlyPoint_->hspd=ArrayValue.toDouble();

                            ArrayValue = obj_pts.value("ht");
                            FlyPoint_->ht=ArrayValue.toDouble();

                            ArrayValue = obj_pts.value("idx");
                            FlyPoint_->idx=ArrayValue.toInt();

                            ArrayValue = obj_pts.value("lat");
                            FlyPoint_->lat=ArrayValue.toDouble();

                            ArrayValue = obj_pts.value("lng");
                            FlyPoint_->lng=ArrayValue.toDouble();

                            ArrayValue = obj_pts.value("presetItv");
                            FlyPoint_->presetItv=ArrayValue.toInt();

                            ArrayValue = obj_pts.value("radius");
                            FlyPoint_->radius=ArrayValue.toInt();

                            ArrayValue = obj_pts.value("recordOnHov");
                            FlyPoint_->recordOnHov=ArrayValue.toInt();

                            ArrayValue = obj_pts.value("spd");
                            FlyPoint_->spd=ArrayValue.toDouble();

                            ArrayValue = obj_pts.value("presets");
                            QJsonArray temp_preset_arr = ArrayValue.toArray();
                            if(temp_preset_arr.size()>0)
                            {
                                CameraPreset_vector = new vector<schedule::CameraPreset*>;
                                CameraPreset_ = new schedule::CameraPreset;
                                for(int i=0;i<temp_preset_arr.size();i++)
                                {
                                    QJsonObject obj_preset = temp_preset_arr[i].toObject();

                                     QJsonValue presetValue = obj_preset.value("idx");
                                     CameraPreset_->idx = presetValue.toInt();

                                     presetValue = obj_preset.value("name");
                                     CameraPreset_->name = presetValue.toString().toStdString();

                                     presetValue = obj_preset.value("fpidx");
                                     CameraPreset_->fpidx = presetValue.toInt();

                                     presetValue = obj_preset.value("fpname");
                                     CameraPreset_->fpname = presetValue.toString().toStdString();

                                     presetValue = obj_preset.value("yaw");
                                     CameraPreset_->yaw = presetValue.toDouble();

                                     presetValue = obj_preset.value("pitch");
                                     CameraPreset_->pitch = presetValue.toDouble();

                                     presetValue = obj_preset.value("focus");
                                     CameraPreset_->focus = presetValue.toDouble();

                                     presetValue = obj_preset.value("snapNum");
                                     CameraPreset_->snapNum = presetValue.toInt();

                                     presetValue = obj_preset.value("snapItv");
                                     CameraPreset_->snapNum = presetValue.toInt();

                                     presetValue = obj_preset.value("resState");
                                     CameraPreset_->resState = presetValue.toInt();

                                     presetValue = obj_preset.value("resMemo");
                                     CameraPreset_->resMemo = presetValue.toString().toStdString();

                                     presetValue = obj_preset.value("xjdId");
                                     CameraPreset_->xjdId = presetValue.toString().toStdString();
                                     CameraPreset_vector->push_back(CameraPreset_);
                                }
                                FlyPoint_->presets=CameraPreset_vector;
                            }
                            FlyPoint_Vector->push_back(FlyPoint_);
                         }
                         FcowDroneRoute_->pts=FlyPoint_Vector;
                         FcowDroneNewRoutePara_->route=FcowDroneRoute_;
                     }
                }
            }
         }
     if(ui->checkBox->isChecked())
     {
         udpCom->dataSend(FcowDroneNewRoutePara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
     }
     else {
         udpCom->dataSend(FcowDroneNewRoutePara_->toJsonString(),ui->addressBox3->text(),ui->PortBox3->text().toInt());
     }
   }
}
/*执行航线*/
void MainWindow::send_ExeAirRoute()
{

    if(ifclicked)
    {
        FcowDroneGoRoutePara_=new schedule::FcowDroneGoRoutePara;  
        FcowDroneGoRoutePara_->routeId=FcowDroneNewRoutePara_->route->id;
        FcowDroneGoRoutePara_->route=FcowDroneNewRoutePara_->route;
        if(ui->checkBox->isChecked())
        {
            udpCom->dataSend(FcowDroneGoRoutePara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
        }
        else
        {
            udpCom->dataSend(FcowDroneGoRoutePara_->toJsonString(),ui->addressBox3->text(),ui->PortBox3->text().toInt());
        }
    }
    else {
        QMessageBox::warning(this,"警告","请先发送航线！");
    }
}
//*************************************************************************************************************************
//吊舱控制********************************************************
/*上*/
void MainWindow::send_GimbalCtrl_Up()
{
    UavGimbalCtrlPara_->dir=33;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
/*下*/
void MainWindow::send_GimbalCtrl_Down()
{
    UavGimbalCtrlPara_->dir=34;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
/*左*/
void MainWindow::send_GimbalCtrl_left()
{
    UavGimbalCtrlPara_->dir=35;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
/*右*/
void MainWindow::send_GimbalCtrl_right()
{
    UavGimbalCtrlPara_->dir=36;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
/*焦距+*/
void MainWindow::send_GimbalCtrl_Focal_Plus()
{
    UavGimbalCtrlPara_->dir=37;
    UavGimbalCtrlPara_->offset+=1;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
/*焦距-*/
void MainWindow::send_GimbalCtrl_Focal_Reduce()
{
    UavGimbalCtrlPara_->dir=37;
    UavGimbalCtrlPara_->offset-=1;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
/*拍照一张*/
void MainWindow::send_GimbalCtrl_Photo()
{
    UavGimbalCtrlPara_->dir=38;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
/*录像开始*/
void MainWindow::send_GimbalCtrl_Record_Start()
{
    UavGimbalCtrlPara_->dir=39;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
/*录像结束*/
void MainWindow::send_GimbalCtrl_Record_End()
{
    UavGimbalCtrlPara_->dir=40;
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else
    {
        udpCom->dataSend(UavGimbalCtrlPara_->toJsonString(),ui->addressBox4->text(),ui->PortBox4->text().toInt());
    }
}
//***************************************************************

//雷达控制********************************************************
void MainWindow::send_RadarCtrlPara_Scan_Scope()
{
    UavRadarCtrlPara_->dir=33;
    UavRadarCtrlPara_->offset = ui->lineEdit_17->text().toInt();
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavRadarCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else
    {
        udpCom->dataSend(UavRadarCtrlPara_->toJsonString(),ui->addressBox5->text(),ui->PortBox5->text().toInt());
    }
}

void MainWindow::send_RadarCtrlPara_Scan_Speed()
{
    UavRadarCtrlPara_->dir=34;
    UavRadarCtrlPara_->offset = ui->lineEdit_18->text().toInt();
    if(ui->checkBox->isChecked())
    {
        udpCom->dataSend(UavRadarCtrlPara_->toJsonString(),ui->addressBox_all->text(),ui->PortBox_all->text().toInt());
    }
    else {
        udpCom->dataSend(UavRadarCtrlPara_->toJsonString(),ui->addressBox5->text(),ui->PortBox5->text().toInt());
    }
}

//*************************************************************

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->addressBox_all->setEnabled(false);
    ui->PortBox_all->setEnabled(false);
    //UI界面
    //设置表头    
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    //**添加目标******************************************************
    strList<<0<<0<<0<<0<<0<<0<<0<<0;
    dataSetNum = 0;
    /*添加*/
    QObject::connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::SaveDroneTable);
    /*删除*/
    QObject::connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::RemoveDroneTable);
    //***************************************************************

    //添加检测结果*****************************************************
    //设置表头
    ui->tableWidget_2->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    strList_ChkRe<<0<<0<<0;
    dataSetNum_ChkRe = 0;
    /*添加*/
    QObject::connect(ui->pushButton_4,&QPushButton::clicked,this,&MainWindow::SaveChkReslutsTable);
    /*删除*/
    QObject::connect(ui->pushButton_5,&QPushButton::clicked,this,&MainWindow::RemoveChkReslutsTable);
    //***************************************************************

    //飞行控制********************************************************
    /*松刹车*/
    QObject::connect(ui->pushButton_6,&QPushButton::clicked,this,&MainWindow::send_release_break);
    /*刹车*/
    QObject::connect(ui->pushButton_7,&QPushButton::clicked,this,&MainWindow::send_break);
    /*起飞*/
    QObject::connect(ui->pushButton_8,&QPushButton::clicked,this,&MainWindow::send_departure);
    /*返航*/
    QObject::connect(ui->pushButton_9,&QPushButton::clicked,this,&MainWindow::send_GoBackPara);
    /*发送航线*/
    QObject::connect(ui->pushButton_10,&QPushButton::clicked,this,&MainWindow::send_AirRoute);
    /*执行航线*/
    QObject::connect(ui->pushButton_11,&QPushButton::clicked,this,&MainWindow::send_ExeAirRoute);
    //***************************************************************
    //吊舱控制********************************************************
    /*上*/
    QObject::connect(ui->pushButton_17,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_Up);
    /*下*/
    QObject::connect(ui->pushButton_18,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_Down);
    /*左*/
    QObject::connect(ui->pushButton_20,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_left);
    /*右*/
    QObject::connect(ui->pushButton_21,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_right);
    /*焦距+*/
    UavGimbalCtrlPara_->offset=1;
    QObject::connect(ui->pushButton_19,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_Focal_Plus);
    /*焦距-*/
    QObject::connect(ui->pushButton_22,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_Focal_Reduce);
    /*拍照一张*/
    QObject::connect(ui->pushButton_23,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_Photo);
    /*录像开始*/
    QObject::connect(ui->pushButton_24,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_Record_Start);
    /*录像结束*/
    QObject::connect(ui->pushButton_25,&QPushButton::clicked,this,&MainWindow::send_GimbalCtrl_Record_End);
    //***************************************************************

    //雷达控制********************************************************
    /*范围扫描*/
    QObject::connect(ui->pushButton_35,&QPushButton::clicked,this,&MainWindow::send_RadarCtrlPara_Scan_Scope);
    /*扫描速度*/
    QObject::connect(ui->pushButton_36,&QPushButton::clicked,this,&MainWindow::send_RadarCtrlPara_Scan_Speed);
    //***************************************************************
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        ui->addressBox1->setEnabled(false);
        ui->PortBox1->setEnabled(false);
        ui->addressBox2->setEnabled(false);
        ui->PortBox2->setEnabled(false);
        ui->addressBox3->setEnabled(false);
        ui->PortBox3->setEnabled(false);
        ui->addressBox4->setEnabled(false);
        ui->PortBox4->setEnabled(false);
        ui->addressBox5->setEnabled(false);
        ui->PortBox5->setEnabled(false);
        ui->addressBox_all->setEnabled(true);
        ui->PortBox_all->setEnabled(true);
    }
    else {
        ui->addressBox1->setEnabled(true);
        ui->PortBox1->setEnabled(true);
        ui->addressBox2->setEnabled(true);
        ui->PortBox2->setEnabled(true);
        ui->addressBox3->setEnabled(true);
        ui->PortBox3->setEnabled(true);
        ui->addressBox4->setEnabled(true);
        ui->PortBox4->setEnabled(true);
        ui->addressBox5->setEnabled(true);
        ui->PortBox5->setEnabled(true);
        ui->addressBox_all->setEnabled(false);
        ui->PortBox_all->setEnabled(false);
    }
}

void MainWindow::on_pushButton_3_clicked()//添加组播
{
    //添加到组播
    udpSocket_ = new QUdpSocket(this);
    QString IP = ui->addressBox_all->text();
    groupAddress = QHostAddress(IP);
    quint16 groupPort=ui->PortBox_all->text().toInt();
    // QHostAddress::AnyIPv4 与此地址绑定的socket将仅侦听IPv4交互
    // groupPort，多播组统一的一个端口
    // QUdpSocket::ShareAddress 允许其他服务绑定到相同的地址和端口
    // QUdpSocket::ReuseAddressHint 向QAbstractSocket提供提示，提示它应尝试重新绑定服务，即使地址和端口已被另一个套接字绑定。在Windows和Unix上，这相当于SO_REUSEADDR套接字选项。
    // QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint 组合使用才能在本机同时启动多个程序绑定相同端口，适合没有局域网只有一台电脑的本地测试使用
    if (udpSocket_->bind(QHostAddress::AnyIPv4, groupPort, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint)) //先绑定端口
    {
    udpSocket_->joinMulticastGroup(groupAddress); //加入IP地址为groupAddress的多播组，绑定端口groupPort进行通信
    }
    qDebug()<<"print to here!_1"<<groupAddress;
}

void MainWindow::on_pushButton_12_clicked()//删除并退出组播
{
    udpSocket_->leaveMulticastGroup(groupAddress);// 退出组播
    udpSocket_->abort();
}
