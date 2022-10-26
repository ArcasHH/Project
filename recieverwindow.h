#ifndef RECIEVERWINDOW_H
#define RECIEVERWINDOW_H

#include <QWidget>
#include "createfield.h"

namespace Ui {
class RecieverWindow;
}

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QUdpSocket;
class QHostAddress;
class QTcpSocket;
QT_END_NAMESPACE

class RecieverWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RecieverWindow(QWidget *parent = nullptr);
    ~RecieverWindow();

private slots:
    void on_QuitBtn_clicked();
    void on_StartRecieve_clicked();

    void startListen();

private:
    Ui::RecieverWindow *ui;

    CreateField *field = nullptr;

    QTcpSocket *TcpS = nullptr;
    void prepareLayout();
    void EstablishTCP(int Port, QHostAddress const &Addr);
    void createFieldW(int turn);
};

#endif // RECIEVERWINDOW_H
