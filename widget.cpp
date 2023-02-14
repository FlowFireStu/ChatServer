#include "widget.h"
#include "ui_widget.h"
#include "workthread.h"
#include <QJsonArray>
#include <QJsonDocument>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_server = new QTcpServer(this);
    ui->portEdit->setText("63425");

    connect(m_server, &QTcpServer::newConnection, this, &Widget::createThread);
    connect(ui->startBtn, &QPushButton::clicked, this, [=](){
        ui->startBtn->setEnabled(false);
        m_port = ui->portEdit->text().toUShort();
        m_server->listen(QHostAddress::Any, m_port);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::createThread()
{
    QTcpSocket *socket = m_server->nextPendingConnection();
    WorkThread *workthread = new WorkThread(socket);
    workthread->start();
    ui->textBrowser->append(socket->peerAddress().toString() + "已连接");
    connect(workthread, &WorkThread::workFinished, this, [=](){
        workthread->exit();
        workthread->wait();
        workthread->deleteLater();
        ui->textBrowser->append(socket->peerAddress().toString() + "已断开");
    });
}

void Widget::init()
{

}
