#ifndef SERVER_H
#define SERVER_H

#include <QDialog>
#include "recieverwindow.h"

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

private:
    Ui::Server *ui;
    RecieverWindow *window;
};

#endif // SERVER_H
