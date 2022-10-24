#include "menu.h"
#include "ui_menu.h"
#include "server.h"
#include "createwindow.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_pushButton_online_clicked()
{
    Server game;
    game.setModal(true);
    game.exec();
}

void Menu::on_pushButton_exit_clicked()
{
    close();
}

void Menu::on_pushButton_solo_clicked()
{
    window = new CreateWindow;
    window->show();
    this->hide();
}

