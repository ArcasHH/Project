#include "battle.h"
#include "ui_battle.h"
#include "FieldCell.h"
//#include "createfieldwindow.h"
#include <QDebug>

Battle::Battle(QWidget *parent, FieldCell ***Field, int *ptr) :
    QWidget(parent),
    ui(new Ui::Battle),
    ButtonField{Field}
{
    ui->setupUi(this);
    generateEnemyField();
    CreateYourField();
    connect(ui->ExitButton, SIGNAL(clicked()), this, SLOT(close()));
    alive = ptr;
//    for (int i = 0; i != 10; ++i)
//        qDebug() << alive[i];


//    connect(control, &controller::resReady, this, &battle::readRes);
//    connect(control, &controller::pReady, this, &battle::readP);

}

Battle::~Battle()
{
    delete ui;
}


void Battle::generateEnemyField() {
    QGridLayout &Field = *ui->gridLayout_enemy;

    ButtonField_enemy = new FieldCell**[10];
    for (int i = 0; i != 10; ++i)
        ButtonField_enemy[i] = new FieldCell*[10];

    for (int i = 0; i != 10; i++)
        for (int j = 0; j != 10; j++) {
            FieldCell *Btn = new FieldCell(i, j);
            Btn->setFixedSize(50, 50);
            Btn->setText(QString::number(i) + QString::number(j));
            Btn->setStyleSheet("background-color: grey");
            ButtonField_enemy[i][j] = Btn;
            Btn->available = true;
            Btn->ship = ButtonField[j][i]->ship;
            Btn->index = ButtonField[j][i]->index;
            Field.addWidget(Btn, i, j);
            connect(Btn, SIGNAL(clicked()), this, SLOT(buttonClicked_en()));
        }
}

void Battle::CreateYourField(){
    QGridLayout &Field = *ui->gridLayout_your;
    for (int i = 0; i != 10; i++)
        for (int j = 0; j != 10; j++) {
            FieldCell *Btn = ButtonField[i][j];
            Btn->setDisabled(true);
            Btn->setFixedSize(25, 25);
            Field.addWidget(Btn, i, j);
        }
}

// on readP(i, j) {
//    if Filed[i][j] == ship
//      if alive[Fiedld[i][j].index] < 0
//         controller->sendRes(kill)
//      else
//         controller->sendRes(hit)
//    else
//      controller->sendRes(miss)

void Battle::buttonClicked_en() {
    QObject *Sender = QObject::sender();
    FieldCell *Btn = static_cast<FieldCell*>(Sender);
    qDebug() << "Pressed: " << Btn->x << ' ' << Btn->y << ' ' << Btn->index;
    int i = Btn->x;
    int j = Btn->y;

    //contorller->sendTurn(Point(i, j));
    // }

    // This logic goes to readRes {
    //  if res == hit:
    //     draw red:
    //  else if res == kill:
    //     draw black;
    //  else
    //     draw white;
    if(Btn->ship == false)
        Btn->setStyleSheet("background-color: white");
    else if (Btn->ship == true){
        Btn->setStyleSheet("background-color: red");
        // TODO remake
        alive[Btn->index] -= 1;
        //Btn->ship = false;
//        ButtonField_enemy[i+1][j+1]->setStyleSheet("background-color: rgb(100, 100, 100)");
//        ButtonField_enemy[i+1][j-1]->setStyleSheet("background-color: rgb(100, 100, 100)");
//        ButtonField_enemy[i-1][j+1]->setStyleSheet("background-color: rgb(100, 100, 100)");
//        ButtonField_enemy[i-1][j-1]->setStyleSheet("background-color: rgb(100, 100, 100)");
        if( alive[Btn->index] <= 0){
            Btn->setStyleSheet("background-color: black");
        }
        qDebug() << "alive: " << alive[Btn->index];
        }
}
