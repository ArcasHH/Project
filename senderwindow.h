#ifndef SENDERWINDOW_H
#define SENDERWINDOW_H

#include "createfield.h"
#include "SharedDeata.h"
#include <QWidget>
#include <QThread>

namespace Ui {
class SenderWindow;
}

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QUdpSocket;
class QTcpSocket;
class QTcpServer;
QT_END_NAMESPACE


// This class emits several udp packages.
class UdpSender : public QThread {
    Q_OBJECT
    void run() override;
public:
    // TODO figureout hot to sincronize.
    bool Do = true;
    int ListenPort;

    UdpSender(QObject *parent, int Port) : QThread{parent}, ListenPort{Port} {}
};


// SenderWindow is the window this logic of UdpSender and TcpListener.
class SenderWindow : public QWidget
{
    Q_OBJECT
    QThread SenderThread;

public:
    explicit SenderWindow(QWidget *parent = nullptr);
    ~SenderWindow();

private slots:
    void startListenTCP();

    void on_QuitBtn_clicked();

    void on_EmitBtn_clicked();

private:
    Ui::SenderWindow *ui;

    UdpSender *Sender = nullptr;
    QTcpServer *Listener = nullptr;
    QTcpSocket *TcpS = nullptr;

    CreateField *field = nullptr;

    int MsgNo = 1;

    void prepareLayout();
};

#endif // SENDERWINDOW_H


