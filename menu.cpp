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

void Menu::on_pushButton_online_clicked()
{
    Server game;
    game.setModal(true);
    game.exec();
}

void Menu::on_pushButton_solo_clicked()
{
    window = new CreateField(window, new AIController, 1);
    connect(window, SIGNAL(destroyed()), this, SLOT (show()));
    window->show();
    this->hide();
}

void Menu::on_pushButton_exit_clicked()
{
    close();
}

Menu::~Menu()
{
    delete ui;
}

