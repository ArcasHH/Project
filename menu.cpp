#include "menu.h"
#include "ui_menu.h"
#include "server.h"
#include "createfield.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(150, 205, 205)");

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

    window = new CreateField(nullptr, new AIController, 1);
    window->show();
    this->hide();
}

