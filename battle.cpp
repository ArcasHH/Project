#include "battle.h"
#include "ui_battle.h"
#include "FieldCell.h"
#include <QDebug>
#include <QMessageBox>

Battle::Battle(QWidget *parent, controller *control_in, int turn, FieldCell *** Field, int *alive_in) :
    QWidget(parent),
    ui(new Ui::Battle),

    alive(alive_in),
    ButtonField{Field},
    control(control_in)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(150, 205, 205)");
    connect(control, &controller::resReady, this, &Battle::readRes);
    connect(control, &controller::pReady, this, &Battle::readP);

    generateEnemyField();
    CreateYourField();
    setTurnLabel(turn);
}

void Battle::setTurnLabel(bool turn) {
    QString t = turn ? "YOUR TURN" : "ENEMY TURN";
    setEnabled(turn);
    ui->label_turn->setText(t);
}

void Battle::readRes(Result isHit) {
    QString R = isHit == Result::Hit ? "HIT!" : isHit == Result::Kill ? "KILL!!" : "MISS...";
    ui->label_win->setText(tr("recived res: %1").arg(R));

    switch (isHit) {
    case Result::Miss:
        ButtonField_enemy[Px][Py]->setStyleSheet("background-color: rgb(174, 238, 238)");
        ui->label_act->setText("MISS...");
//        this->setEnabled(false);
        setTurnLabel(0);
        break;
    case Result::Hit:
        ButtonField_enemy[Px][Py]->setStyleSheet("background-color: rgb(205, 96, 144)");
        ui->label_act->setText("HIT!");
//        this->setEnabled(true);
        setTurnLabel(1);
        break;
    case Result::Kill:
        ButtonField_enemy[Px][Py]->setStyleSheet("background-color: rgb(139, 58, 98)");
        ui->label_act->setText("KILL!!!");
        --num_alive;
        if(num_alive <= 0){
            QMessageBox::information(nullptr, "SEA BATTLE", "EEE!!!WIN!!!!");
            //ui->label_win->setText("EEE!!!YOU WIN!!!!");
            close();
        }
//        this->setEnabled(true);
        setTurnLabel(1);
        break;
    }
    //setTurnLabel(0);
}

void Battle::readP(Point P) {
    //ui->label_win->setText("recieved p: " + QString::number(P.x) + ' ' + QString::number(P.y));
    //qDebug() << P.x << ' ' << P.y;
    FieldCell *Cell = ButtonField[P.x][P.y];

    if (Cell->ship) {
        alive[Cell->index] -= 1;
        if (alive[Cell->index] <= 0) {
            Cell->setStyleSheet("background-color: rgb(139, 58, 98)");
            control->sendFeedback(Result::Kill);
            ++num_killed;
            if (num_killed >= 10) {
                QMessageBox::information(nullptr, "SEA BATTLE", "DEFEAT(((");
                //ui->label_win->setText("YOU DIED...");
                close();
            }
        } else {
            Cell->setStyleSheet("background-color: rgb(205, 96, 144)");
            control->sendFeedback(Result::Hit);
        }
        setTurnLabel(0);
    } else {
        Cell->setStyleSheet("background-color: rgb(174, 238, 238)");
        control->sendFeedback(Result::Miss);
        setTurnLabel(1);
    }
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
            //Btn->setText(QString::number(i) + QString::number(j));
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

void Battle::buttonClicked_en() {

    QObject *Sender = QObject::sender();
    FieldCell *Btn = static_cast<FieldCell*>(Sender);
    Btn->setEnabled(false);
    Px = Btn->x;
    Py = Btn->y;

    Point P;
    P.x = Px;
    P.y = Py;

    control->sendTurn(P);
}

void Battle::on_ExitButton_clicked()
{
    close();
}

Battle::~Battle()
{
    delete ui;
}
