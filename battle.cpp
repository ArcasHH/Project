#include "battle.h"
#include "ui_battle.h"
#include "FieldCell.h"
#include "enemyfields.h"
//#include "createfieldwindow.h"
#include <QDebug>
#include <QMessageBox>

int Px = 0;
int Py = 0;
bool win = false;

Battle::Battle(QWidget *parent, controller *control_in, int turn, FieldCell *** Field) :
    QWidget(parent),
    ui(new Ui::Battle),
    ButtonField{Field},
    control(control_in)
{
    ui->setupUi(this);

    connect(control, &controller::resReady, this, &Battle::readRes);
    connect(control, &controller::pReady, this, &Battle::readP);

    setTurnLabel(turn);

    generateEnemyField();
    CreateYourField();
    //alive = ptr;
//    for (int i = 0; i != 10; ++i)
//        qDebug() << alive[i];
}

void Battle::setTurnLabel(int turn) {

    QString t = turn ? "ВАШ ХОД" : "ХОД ВРАГА";
    ui->label_turn->setText(t);
}

void Battle::readRes(Result isHit) {
    QString R = isHit == Result::Hit ? "РАНИЛ!" : isHit == Result::Kill ? "УБИЛ!!" : "МИМО...";
    ui->label_win->setText(tr("recived res: %1").arg(R));

    switch (isHit) {
    case Result::Miss:
        ButtonField_enemy[Px][Py]->setStyleSheet("background-color: white");
        ui->label_act->setText("МИМО...");
        break;
    case Result::Hit:
        ButtonField_enemy[Px][Py]->setStyleSheet("background-color: red");
        ui->label_act->setText("РАНИЛ!");
        break;
    case Result::Kill:
        ButtonField_enemy[Px][Py]->setStyleSheet("background-color: black");
        ui->label_act->setText("УБИЛ!!!");
        break;
    }

    setTurnLabel(0);
}

void Battle::readP(Point P) {
    ui->label_win->setText("recieved p: " + QString::number(P.x) + ' ' + QString::number(P.y));
    qDebug() << P.x << ' ' << P.y;
    //qDebug() << "rerererererere" << alive[ButtonField[P.x][P.y]->index];
//    ui->responce->setText(tr("recived p: %1 %1").arg(P.x).arg(P.y));
    if (ButtonField[P.x][P.y]->ship) {
       control->sendFeedback(Result::Hit);
       //alive[ButtonField[Px][Py]->index] -=1;
       //if(alive[ButtonField[P.x][P.y]->index]<= 0)
           //control->sendFeedback(Result::Kill);

    }
    else
        control->sendFeedback(Result::Miss);

    setTurnLabel(1);
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
    Px = Btn->x;
    Py = Btn->y;

    Point P;
    P.x = Px;
    P.y = Py;
    if(alive[0]<=0 && alive[1]<=0 && alive[2]<=0 && alive[3]<=0 && alive[4]<=0 && alive[5]<=0 && alive[6]<=0 &&
            alive[7]<=0 && alive[8]<=0 && alive[9]<=0){
        QMessageBox::information(this, "","УРА!!!ПОБЕДА!!!!");
     }
    control->sendTurn(P);

    //contorller->sendTurn(Point(i, j));
    // }

    // This logic goes to readRes {
    //  if res == hit:
    //     draw red:
    //  else if res == kill:
    //     draw black;
    //  else
    //     draw white;
    /*
    if(Btn->ship == false){
        Btn->setStyleSheet("background-color: white");
        ui->label->setText("МИМО...");
    }
    else if (Btn->ship == true){
        Btn->setStyleSheet("background-color: red");
        ui->label->setText("РАНИЛ!");
        // TODO remake
        alive[Btn->index] -= 1;
        //Btn->ship = false;
//        ButtonField_enemy[i+1][j+1]->setStyleSheet("background-color: rgb(100, 100, 100)");
//        ButtonField_enemy[i+1][j-1]->setStyleSheet("background-color: rgb(100, 100, 100)");
//        ButtonField_enemy[i-1][j+1]->setStyleSheet("background-color: rgb(100, 100, 100)");
//        ButtonField_enemy[i-1][j-1]->setStyleSheet("background-color: rgb(100, 100, 100)");
        if( alive[Btn->index] <= 0){
            Btn->setStyleSheet("background-color: black");
            ui->label->setText("УБИЛ!");
        }
        qDebug() << "alive: " << alive[Btn->index];
        }
        */
}

void Battle::on_ExitButton_clicked()
{
    close();
}

