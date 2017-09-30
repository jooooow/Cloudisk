#ifndef TCP_SENDER_H
#define TCP_SENDER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QByteArray>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include <QFileInfo>
#include <QHostAddress>
#include <QTime>
#include <QDebug>
#include <QCoreApplication>

class Tcp_Sender : public QObject
{
    Q_OBJECT
private:
    QTcpServer* sender;
    QTcpSocket* receiver;
    QFile* current_file;
    QString current_file_path;
    QString current_file_name;
    qint64 current_file_size;
    QHostAddress current_reciver_address;
    QByteArray buf;
    int current_reciver_port;
public:
    Tcp_Sender();
    ~Tcp_Sender();
    void openFile();
    void openFile(const QString& file_name);
    //void sendData();
private slots:
    void onDisconnected();
    void onNewConnection();
public slots:
    void onStartListen();
signals:
    void hasNewConnection(QString ip, qint64 port);
    void updateBar(int value);
    void fin();
private:
    void init();
    void startListen(const QHostAddress& add = QHostAddress::Any, qint64 port = 0);
    void sleep(unsigned int msec)
    {
        QTime dieTime = QTime::currentTime().addMSecs(msec);
        while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
};

#endif // TCP_SENDER_H
