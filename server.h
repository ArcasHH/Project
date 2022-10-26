#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include "recieverwindow.h"
#include "senderwindow.h"

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void on_back_clicked();

    void on_pushButton_reciever_clicked();

    void on_pushButton_sender_clicked();

private:
    Ui::Server *ui;
    RecieverWindow *window;
    SenderWindow *window_send;
};

#endif // SERVER_H
