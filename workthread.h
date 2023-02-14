#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

class WorkThread : public QThread
{
    Q_OBJECT
private:
    QTcpSocket* m_socket;

    void processRequest();
    void logoutAccount();
public:
    explicit WorkThread(QTcpSocket* socket, QObject *parent = nullptr);
    ~WorkThread();

    void run() override;

signals:
    void workFinished();

};

#endif // WORKTHREAD_H
