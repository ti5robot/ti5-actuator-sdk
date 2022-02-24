#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "actuator_control_interface.h"

int route1[1001]={0};
int route2[1001]={0};

int route3[1001]={0};
int route4[1001]={0};
int route5[1001]={0};

int route6[1001]={0};

int numnum123=0;

int last_num= 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("电机控制上位机");
    uiTimer.connect(&uiTimer,SIGNAL(timeout()),this, SLOT(elapsed_time()));
    uiTimer.start(4);
    QSerialPortInfo inf;
    QList<QSerialPortInfo> ls=inf.availablePorts();
    QString str1;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        str1+="Name : ";
        str1+=info.portName();
        str1+="\nDescription : ";
        str1+=info.description();
        str1+="\nManufacturer: ";
        str1+=info.manufacturer();
        str1+="\nSerial Number: ";
        str1+=info.serialNumber();
        str1+="\nSystem Location: ";
        str1+=info.systemLocation();
        str1+="\n";

    }

    QFile file("../route.txt");


    //轨迹读取，现改装成tcp 收取轨迹,最终采集到的数据都存在route中
    file.open(QIODevice::ReadWrite);
    file.write("123");
    file.close();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::elapsed_time()
{
    switch (this->ACI.ACSM.State)
    {
    case IDLE:
    {
        if(this->ACI.ACSM.NextState == FIND_ACT)
        {
            this->ACI.ACSM.State = IDLE_START;
        }
    }
        break;
    case IDLE_START:
    {
        if(this->serialPortConnect)
        {
            if(this->ACI.ACSM.NextState == FIND_ACT)
            {
                this->ACI.ACSM.State = FIND_ACT;
            }
        }
        else
        {
            if(this->ufcp.open(this->serialportName))
            {
                this->serialPortConnect = true;
                qDebug()<<"connect serial OK";
            }
            else
            {
                this->serialPortConnect = false;
                qDebug()<<"connect serial failed";
                DialogNotice notice(QString("串口打开失败"));
                notice.exec();
                this->ACI.ACSM.NextState = IDLE;
                this->ACI.ACSM.State = IDLE;
                return;
            }
        }
    }
        break;
    case FIND_ACT:
    {
        uint8_t canidlist[10]={0},cmd[10]={2};
        uint32_t parameterlist[10]={0};

        if(ufcp.readCommand(0,canidlist,cmd,parameterlist)>0)
        {
            this->ACI.ACSM.NextState = CONTROL_ACT;
            this->ACI.ACSM.State = CONTROL_ACT;

            uint8_t canidlist2[10]={0},cmd2[10]={4};
            uint32_t parameterlist2[10]={0};

            ufcp.sendCommand(0,canidlist2,cmd2,parameterlist2);
            ufcp.sendCommand(0,canidlist2,cmd2,parameterlist2);
        }
        else
        {
            uint8_t canidlist2[10]={0},cmd2[10]={2};
            uint32_t parameterlist2[10]={0};
            ufcp.sendCommand(0,canidlist2,cmd2,parameterlist2);
        }


    }
        break;
    case CONTROL_ACT:
    {
        int cn[6];
        int32_t parameterlist2[10]={0};
        uint8_t canidlist[10]={0},cmd[10]={0};
        uint8_t canidlist2[10]={1,2,3,4,5,6},cmd2[10]={SET_REG_TARGET_POSITION,SET_REG_TARGET_POSITION,SET_REG_TARGET_POSITION,SET_REG_TARGET_POSITION,SET_REG_TARGET_POSITION,SET_REG_TARGET_POSITION};
        int numnumnum;
        if (numnum123-1-last_num==2){numnumnum=numnum123-1;}
        else if(numnum123-1-last_num==3){numnumnum=numnum123-2;}
        else if(numnum123-1-last_num==4){numnumnum=numnum123-3;}
        else if(numnum123-1-last_num==5){numnumnum=numnum123-4;}
        else{numnumnum=numnum123;}

        cn[0]=route1[numnumnum-1]-route1[numnumnum-2];
        cn[1]=route2[numnumnum-1]-route2[numnumnum-2];
        cn[2]=route3[numnumnum-1]-route3[numnumnum-2];
        cn[3]=route4[numnumnum-1]-route4[numnumnum-2];
        cn[4]=route5[numnumnum-1]-route5[numnumnum-2];
        cn[5]=route6[numnumnum-1]-route6[numnumnum-2];


        int round_i;

        if (abs(cn[0])<1000&&abs(cn[1]<1000)&&abs(cn[2]<1000)&&abs(cn[3])<1000&&abs(cn[4]<1000)&&abs(cn[5]<1000)){
            round_i=10;
        }
        else if(abs(cn[0])<10000&&abs(cn[1]<10000)&&abs(cn[2]<10000)&&abs(cn[3])<10000&&abs(cn[4]<10000)&&abs(cn[5]<10000))
        {round_i=50;}

        else if(abs(cn[0])<50000&&abs(cn[1]<50000)&&abs(cn[2]<50000)&&abs(cn[3])<50000&&abs(cn[4]<50000)&&abs(cn[5]<50000))
        {round_i=200;}

        else if(abs(cn[0])<100000&&abs(cn[1]<100000)&&abs(cn[2]<100000)&&abs(cn[3])<100000&&abs(cn[4]<100000)&&abs(cn[5]<100000))
        {round_i=500;}
        else if(abs(cn[0])<500000&&abs(cn[1]<500000)&&abs(cn[2]<500000)&&abs(cn[3])<500000&&abs(cn[4]<500000)&&abs(cn[5]<500000))
        {round_i=1000;}
        else if(abs(cn[0])<10000000&&abs(cn[1]<10000000)&&abs(cn[2]<10000000)&&abs(cn[3])<10000000&&abs(cn[4]<10000000)&&abs(cn[5]<10000000))
        {round_i=2000;}

        else {
        round_i=5;
        }

              if(numnumnum-1!=last_num) {

            r1[10000]={0};
            r2[10000]={0};
            r3[10000]={0};
            r4[10000]={0};
            r5[10000]={0};
            r6[10000]={0};

         for (int i=0;i<round_i;i++) {

                         if (cn[0]<0)
                         {
                             r1[i]=route1[numnumnum-2]-i*abs(int(cn[0]/round_i));
                         }

                         else if(cn[0]>0)
                         {
                             r1[i]=route1[numnumnum-2]+i*abs(int(cn[0]/round_i));
                         }

                         if (cn[1]<0)
                         {
                             r2[i]=route2[numnumnum-2]-i*abs(int(cn[1]/round_i));


                         }

                         else if(cn[1]>0)
                         {
                             r2[i]=route2[numnumnum-2]+i*abs(int(cn[1]/round_i));

                         }

                         if (cn[2]<0)
                         {
                             r3[i]=route3[numnumnum-2]-i*abs(int(cn[2]/round_i));

                         }

                         else if(cn[2]>0)
                         {
                             r3[i]=route3[numnumnum-2]+i*abs(int(cn[2]/round_i));

                         }

                         if (cn[3]<0)
                         {
                             r4[i]=route4[numnumnum-2]-i*abs(int(cn[3]/round_i));

                         }

                         else if(cn[3]>0)
                         {
                             r4[i]=route4[numnumnum-2]+i*abs(int(cn[3]/round_i));

                         }

                         if (cn[4]<0)
                         {
                             r5[i]=route5[numnumnum-2]-i*abs(int(cn[4]/round_i));

                         }

                         else if(cn[4]>0)
                         {
                             r5[i]=route5[numnumnum-2]+i*abs(int(cn[4]/round_i));

                         }

                         if (cn[5]<0)
                         {
                             r6[i]=route6[numnumnum-2]-i*abs(int(cn[5]/round_i));

                         }

                         else if(cn[5]>0)
                         {
                             r6[i]=route6[numnumnum-2]+i*abs(int(cn[5]/round_i));

                         }

                         parameterlist2[0] = r1[i];
                         parameterlist2[1] = r2[i];
                         parameterlist2[2] = r3[i];
                         parameterlist2[3] = r4[i];
                         parameterlist2[4] = r5[i];
                         parameterlist2[5] = r6[i];
                         last_num=numnumnum-1;
                         ufcp.sendCommand(6,canidlist2,cmd2,(uint32_t*)parameterlist2);
                         ufcp.readCommand(6,canidlist,cmd,(uint32_t*)parameterlist2);


}

         }
          else{last_num=numnumnum-1;}

    }}}

void MainWindow::on_pushButton_findActuator_released()
{

    if(this->ACI.ACSM.State == IDLE)
    {
        this->ACI.ACSM.NextState = FIND_ACT;
        qDebug()<<"NextState"<<this->ACI.ACSM.NextState;
    }
}

void MainWindow::on_pushButtonTCP_clicked()
{
    QApplication a(int argc,char *argv);
    mainui = new server;
    QVBoxLayout *tcplay1=new QVBoxLayout;
    tcplay1->addWidget(mainui);
}

void MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

}
;

void MainWindow::qt_write_csv_test(int aa)
{
    //qDebug()<<"--------";
   QFile outFile("D:/1.csv");
   QStringList lines;
   lines <<QString::number(r1[aa])<<","<<QString::number(r2[aa])<<","<<QString::number(r3[aa])<<"\n";
   //lines << "00,01,02\n" << "10,11,12\n" << "20,21,22";
   /*如果以ReadWrite方式打开，不会把所有数据清除，如果文件原来的长度为100字节，写操作写入了30字节，那么还剩余70字节，并且这70字节和文件打开之前保持一直*/
   if (outFile.open(QIODevice::Append))
   {
    for (int i = 0; i < lines.size(); i++)
    {
        outFile.write(lines[i].toStdString().c_str());/*写入每一行数据到文件*/
    }
    outFile.close();
   }
}



