#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    QJsonObject m_config;
    QTcpServer *m_server;
    ushort m_port;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void createThread();

private:
    Ui::Widget *ui;

    void init();
};
#endif // WIDGET_H
