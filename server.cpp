#include "server.h"
#include <QDebug>
#include <QTime>
#include <global.h>
//QTimer uiTimer;
server::server(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("TCP server");
    tcpserver =new QTcpServer(this);
    tcpsocket =new QTcpSocket(this);
    tcpserver->listen(QHostAddress::Any,8888);
    qDebug()<<tcpserver->isListening();
    connect(tcpserver,SIGNAL(newConnection()),this,SLOT(newconnection()));
    text1=new QTextBrowser;
    QVBoxLayout *lay1=new QVBoxLayout(this);

    label1 = new QLabel("Recieve:");
    lay1->addWidget(label1);
    lay1->addWidget(text1);
    text1->append("Start recieve…");

}

void server::newconnection()
{
    qDebug()<<"new connection is found";

agvcommui = new MainWindow;

    while(tcpserver->hasPendingConnections())
    {
        tcpsocket = tcpserver->nextPendingConnection();
        connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(readyread()));
        qDebug()<<"local IP:"<<tcpsocket->localAddress();
    }
}

char server::readyread()
{

    Sleep(1);
    char* b;
    char c;
    int32_t cnt = 0;
    int32_t old_target_position0;
    int32_t old_target_position1;
    int32_t old_target_position2;
    int32_t old_target_position3;
    int32_t old_target_position4;
    int32_t old_target_position5;
    while(tcpsocket->bytesAvailable()>0)
    {

        int32_t vv=0;
        cnt++;
        QString a=tcpsocket->readAll();
        if(a!=""){
            agvcommui->sleep(1*2);
            text1->append(a);
            int tem_num =numnum123;
            QStringList fruits =a.split(",");
            QStringList ffruits ;
            ffruits        = fruits.filter(" ");
            int ii=0;
            foreach (const QString &str, ffruits)
            {
                QStringList perPosition =str.split(" ");
                     QStringList qq=perPosition[0].split("&");
                     float value_position = qq[0].toFloat();
                     route1[numnum123]=int(value_position);
                     QStringList qq1=perPosition[1].split("&");
                     float value_position1 = qq1[0].toFloat();
                     route2[numnum123]=int(value_position1);
                     QStringList qq2=perPosition[2].split("&");
                     float value_position2 = qq2[0].toFloat();
                     route3[numnum123]=int(value_position2);
                     QStringList qq3=perPosition[3].split("&");
                     float value_position3 = qq3[0].toFloat();
                     route4[numnum123]=int(value_position3);
                     QStringList qq4=perPosition[4].split("&");
                     float value_position4 = qq4[0].toFloat();
                     route5[numnum123]=int(value_position4);
                     QStringList qq5=perPosition[5].split("&");
                     float value_position5 = qq5[0].toFloat();
                     route6[numnum123]=int(value_position5);
                     qDebug()<<value_position<<"**"<<value_position1<<"**"<<value_position2<<"**"<<value_position3<<"**"<<value_position4<<"**"<<value_position5;
                    ii=ii+1;

if(numnum123==1000){

route1[0]=value_position;route1[1]=value_position;route1[2]=value_position;route1[3]=value_position;route1[4]=value_position;route1[5]=value_position;
route2[0]=value_position1;route2[1]=value_position1;route2[2]=value_position1;route2[3]=value_position1;route2[4]=value_position1;route2[5]=value_position1;
route3[0]=value_position2;route3[1]=value_position2;route3[2]=value_position2;route3[3]=value_position2;route3[4]=value_position2;route3[5]=value_position2;
route4[0]=value_position3;route4[1]=value_position3;route4[2]=value_position3;route4[3]=value_position3;route4[4]=value_position3;route4[5]=value_position3;
route5[0]=value_position4;route5[1]=value_position4;route5[2]=value_position4;route5[3]=value_position4;route5[4]=value_position4;route5[5]=value_position4;
route6[0]=value_position5;route6[1]=value_position5;route6[2]=value_position5;route6[3]=value_position5;route6[4]=value_position5;route6[5]=value_position5;

numnum123=5;
}
            }


numnum123++;


        }}
}
