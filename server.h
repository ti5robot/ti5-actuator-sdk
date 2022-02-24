#ifndef SERVER_H
#define SERVER_H
#include <global.h>

#include <QTcpServer>
#include <QTcpSocket>
#include <QWidget>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

class server : public QWidget
{
    Q_OBJECT
public:
    explicit server(QWidget *parent = nullptr);

    QTcpServer *tcpserver;
    QTcpSocket *tcpsocket;
    QTextBrowser *text1;
    QVBoxLayout *lay1;
    QLabel *label1;
    int _high;
    int _width;
signals:
    void _sizechange(int,int);

public slots:

    void newconnection();
    char readyread();
};
#endif // SERVER_H
