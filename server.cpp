#include "server.h"
#include "ui_server.h"
#include "recieverwindow.h"
#include "senderwindow.h"


Server::Server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
}

Server::~Server()
{
    delete ui;
}

void Server::on_back_clicked()
{
    close();
}

void Server::on_pushButton_reciever_clicked()
{
    window = new RecieverWindow;
    window->show();
    this->hide();
}


void Server::on_pushButton_sender_clicked()
{
    window_send = new SenderWindow;
    window_send->show();
    this->hide();
}

