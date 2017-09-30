#include "tcp_sender.h"

Tcp_Sender::Tcp_Sender()
{
    init();
}

Tcp_Sender::~Tcp_Sender()
{
    if(receiver != nullptr)
        delete receiver;
}

void Tcp_Sender::init()
{
    current_file = nullptr;
    receiver = nullptr;
    sender = new QTcpServer(this);
}

void Tcp_Sender::startListen(const QHostAddress& add, qint64 port)
{
    //_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
    qDebug()<<"listening..";
    if(!sender->listen(add,8888))
        return;
    connect(sender,&QTcpServer::newConnection,[this]()
    {
        qDebug()<<"new connection!";
        this->receiver = sender->nextPendingConnection();
        this->current_reciver_address = this->receiver->peerAddress();
        this->current_reciver_port = this->receiver->peerPort();
        emit hasNewConnection(this->current_reciver_address.toString(),this->current_reciver_port);
        connect(this->receiver,&QTcpSocket::disconnected,this,&Tcp_Sender::onDisconnected);
    });
    connect(sender,&QTcpServer::newConnection,this,&Tcp_Sender::onNewConnection);
}

void Tcp_Sender::openFile()
{
    QString temp_file_path = QFileDialog::getOpenFileName(0,"select a file","E:/");
    if(temp_file_path.isEmpty())
        return;
    current_file_path = temp_file_path;
    current_file_name = current_file_path.right(current_file_path.size() - current_file_path.lastIndexOf("/") - 1);
    current_file = new QFile(current_file_path);
}

void Tcp_Sender::openFile(const QString &file_name)
{
    if(file_name.isEmpty())
        return;
    current_file_path = "E:/" + file_name;
    current_file_name = file_name;
    current_file = new QFile(current_file_path);
}

void Tcp_Sender::onDisconnected()
{
    qDebug()<<"disconnected..";
    receiver->deleteLater();
    receiver = nullptr;
}

void Tcp_Sender::onNewConnection()
{
    connect(this,&Tcp_Sender::fin,this,&Tcp_Sender::onDisconnected);
    int count = 0;
    while(count <= 100)
    {
        emit updateBar(count);
        qDebug()<<count;
        sleep(50);
        count++;
    }
    emit fin();
}

void Tcp_Sender::onStartListen()
{
    qDebug()<<"onstartlisten";
    startListen();
}
