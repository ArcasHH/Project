#include "createfield.h"
#include "ui_createfield.h"
#include "communicator.h"
#include "menu.h"

#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

CreateField::CreateField(QWidget *parent, controller *c, int turn) :
    QWidget(nullptr),
    ui(new Ui::CreateWindow),
    C{c}, t{turn}
{
    ui->setupUi(this);
    this->setStyleSheet("background-color:rgb(150, 205, 205)");

    connect(ui->pushButton_accept, &QPushButton::clicked, this, &CreateField::fieldCreated);
    connect(C, &controller::fReady, this, &CreateField::enemyFieldCreated);

    generateButtons();
    ui->radioButton_vertical->setChecked(true);

    num4 = 1;//amount ships of suh type
    num3 = 2;
    num2 = 3;
    num1 = 4;
    iteration = 0;//for creating

    for (int i = 0; i != 10; ++i)//massive of ship lengths
        alive[i] = 999;
}

void CreateField::fieldCreated() {
    C->sendFieldReady();
    ui->pushButton_accept->setDisabled(true);
    ui->pushButton_clear->setDisabled(true);
    My = true;
    checkready();
}

void CreateField::enemyFieldCreated() {
    En = true;
    checkready();
}

void CreateField::on_pushButton_back_clicked()
{
    ui->pushButton_clear->click();
    close();
}

void CreateField::generateButtons() {//creating of field
    QGridLayout &Field = *ui->fieldGrid;

    ButtonField = new FieldCell**[10];
    for (int i = 0; i != 10; ++i)
        ButtonField[i] = new FieldCell*[10];

    for (int i = 0; i != 10; i++)
        for (int j = 0; j != 10; j++) {
            FieldCell *Btn = new FieldCell(i, j);
            Btn->setFixedSize(50, 50);
            //Btn->setText(QString::number(i) + QString::number(j));
            Btn->setStyleSheet("background-color: grey");
            ButtonField[i][j] = Btn;
            Btn->available = true;
            Btn->index = 42;
            Field.addWidget(Btn, i, j);
            connect(Btn, SIGNAL(clicked()), this, SLOT(buttonClicked()));
        }
}


void CreateField::buttonClicked() {
    QObject *Sender = QObject::sender();
    FieldCell *Btn = static_cast<FieldCell*>(Sender);
    qDebug() << "Pressed: " << Btn->x << ' ' << Btn->y;
    int size = 0;
    bool a = true;//ability to place a ship
    int i = Btn->x;
    int j = Btn->y;
    int num;

    if( ui->radioButton_4->isChecked()){//choise of length of ship
        size = 4;
        num = num4;
    }
    if( ui->radioButton_3->isChecked()){
        size = 3;
        num = num3;
    }
    if( ui->radioButton_2->isChecked()){
        size = 2;
        num = num2;
    }
    if( ui->radioButton_1->isChecked()){
        size = 1;
        num = num1;
    }

    if( (i + size > 10 && ui->radioButton_vertical->isChecked())
            || (j + size > 10 && ui->radioButton_gorizontal->isChecked()) || num <=0)//stop if ship out
        return ;

    if(ui->radioButton_vertical->isChecked() && size != 0 && size > 0){
        for (int n = 0; n != size; n++) {
            if(!ButtonField[i+n][j]->available)
                a = false;
        }
        if(a){//when drawing a ship, it is not superimposed on non-permissible cells
            for (int n = -1; n != size+1; n++) {
                if(i + n >= 0){
                    if( j - 1 >= 0 && i + n <= 9){
                        ButtonField[i+n][j-1]->available = false;
                        ButtonField[i+n][j-1]->setStyleSheet("background-color: rgb(100, 100, 100)");
                    }
                    if(i + n <= 9){
                        ButtonField[i+n][j]->available = false;
                        ButtonField[i+n][j]->setStyleSheet("background-color: rgb(100, 100, 100)");
                    }
                    if( j + 1 <= 9 && i + n <= 9){
                        ButtonField[i+n][j+1]->available = false;
                        ButtonField[i+n][j+1]->setStyleSheet("background-color: rgb(100, 100, 100)");
                    }
                }
            }
            for (int n = 0; n != size; n++) {
                ButtonField[i+n][j]->setStyleSheet("background-color: rgb(205, 96, 144)");
                ButtonField[i+n][j]->ship = true;
                qDebug() << "it: " << iteration;
                ButtonField[i+n][j]->index = iteration;
            }
            if(iteration < 10){
                qDebug() << "size: " << size;
                alive[iteration] = size;
                ++iteration;

            }
            num = num - 1;
        }
    }
    else if(ui->radioButton_gorizontal->isChecked()  && size != 0 && size > 0){
        bool a = true;

        for (int n = 0; n != size; n++) {
            if(!ButtonField[i][j+n]->available)
                a = false;
        }
        if(a){//when drawing a ship, it is not superimposed on non-permissible cells
            for (int n = -1; n != size+1; n++) {
                if(j + n >= 0){
                    if( i - 1 >= 0 && j + n <= 9){
                        ButtonField[i-1][j+n]->available = false;
                        ButtonField[i-1][j+n]->setStyleSheet("background-color: rgb(100, 100, 100)");
                    }
                    if(j + n <= 9){
                        ButtonField[i][j+n]->available = false;
                        ButtonField[i][j+n]->setStyleSheet("background-color: rgb(100, 100, 100)");
                    }
                    if( i + 1 <= 9 && j + n <= 9){
                        ButtonField[i+1][j+n]->setStyleSheet("background-color: rgb(100, 100, 100)");
                        ButtonField[i+1][j+n]->available = false;
                    }
                }
            }
            for (int n = 0; n != size; ++n) {
                ButtonField[i][j+n]->setStyleSheet("background-color: rgb(205, 96, 144)");
                ButtonField[i][j+n]->ship = true;
                ButtonField[i][j+n]->index = iteration;
            }
            if(iteration < 10){
                alive[iteration] = size;
                iteration = iteration + 1;
            }
            num = num - 1;
        }
    }
    QString new_label;
    if( ui->radioButton_4->isChecked()){
        num4 = num;
        new_label = QString::number(num4, 'g', 20);
        ui->label_4->setText(new_label);
    }
    if( ui->radioButton_3->isChecked()){
        num3 = num;
        new_label = QString::number(num3, 'g', 20);
        ui->label_3->setText(new_label);
    }
    if( ui->radioButton_2->isChecked()){
        num2 = num;
        new_label = QString::number(num2, 'g', 20);
        ui->label_2->setText(new_label);
    }
    if( ui->radioButton_1->isChecked()){
        num1 = num;
        new_label = QString::number(num1, 'g', 20);
        ui->label_1->setText(new_label);
    }
   //for(int i=0; i<10; i++)
       //qDebug() << alive[i];
}


void CreateField::on_pushButton_clear_clicked()
{
    //ui->label_accept->setText("");
    iteration = 0;
    num4 = 1;
    num3 = 2;
    num2 = 3;
    num1 = 4;
    ui->label_4->setText(QString::number(num4, 'g', 20));
    ui->label_3->setText(QString::number(num3, 'g', 20));
    ui->label_2->setText(QString::number(num2, 'g', 20));
    ui->label_1->setText(QString::number(num1, 'g', 20));
    for (int i = 0; i != 10; ++i){
        alive[i] = 999;
        for (int j = 0; j != 10; ++j){
             ButtonField[i][j]->setStyleSheet("background-color: grey");
             ButtonField[i][j]->available = true;
        }
    }
}
void CreateField::checkready() {
    if (!(My && En))
        return;
    else if(num4 + num3 + num2 + num1 == 0){
        ui->label_accept->setText("EEEE");
        game = new Battle(nullptr, C, t, ButtonField, alive);
        game->show();
        this->hide();
    }
}

void CreateField::on_pushButton_accept_clicked()//CreateButton
{
    if(num4 + num3 + num2 + num1 == 0){
        ui->label_accept->setText("WAITING...");
        checkready();
    }
    else
        QMessageBox::warning(this, "SEA BATTLE", "NOT ALL SHIPS ARE ON THE BATTLEFIELD (if they don't fit, then clear the field and try again");
}

CreateField::~CreateField()
{
    for (int i = 0; i != 10; ++i)
        for (int j = 0; j != 10; ++j)
            delete ButtonField[i][j];
    for (int i = 0; i != 10; ++i)
        delete[] ButtonField[i];
    delete[] ButtonField;

    delete ui;
}
