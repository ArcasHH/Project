#include "battle.h"
#include "ui_battle.h"
#include "FieldCell.h"
//#include "createfieldwindow.h"
#include <QDebug>

Battle::Battle(QWidget *parent, FieldCell ***Field) :
    QWidget(parent),
    ui(new Ui::Battle),
    ButtonField{Field}
{
    ui->setupUi(this);
    generateEnemyField();
    CreateYourField();
    connect(ui->ExitButton, SIGNAL(clicked()), this, SLOT(close()));
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


void Battle::buttonClicked_en() {
    QObject *Sender = QObject::sender();
    FieldCell *Btn = static_cast<FieldCell*>(Sender);
    qDebug() << "Pressed: " << Btn->x << ' ' << Btn->y;
    if(Btn->ship == false)
        Btn->setStyleSheet("background-color: white");
    else if (Btn->ship == true)
        Btn->setStyleSheet("background-color: red");
}
