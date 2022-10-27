#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "point.h"
#include "FieldCell.h"

#include <QObject>
#include <QRandomGenerator>
#include <QDebug>

struct AIPlayer : public QObject {
    Q_OBJECT

signals:
    void turnMade(Point);
    void turnChecked(Result);

public:

    void getTurn(Point P) { //отправка ботом результата о нажатой игроком кнопки
        qDebug() << "Bot recieved move: " << P.x << ' ' << P.y;
        if(ButtonField_en[P.x][P.y]->ship && alive[ButtonField_en[P.x][P.y]->index] <= 1){
            alive[ButtonField_en[P.x][P.y]->index] -= 1;
            emit turnChecked(Result::Kill);
        }
        else if (ButtonField_en[P.x][P.y]->ship) {
            alive[ButtonField_en[P.x][P.y]->index] -= 1;
            emit turnChecked(Result::Hit);

        } else
            emit turnChecked(Result::Miss);
        makeTurn();
     }
    void getRes(Result r) {
         QString R = r == Result::Hit ? "Hit" : r == Result::Kill ? "Kill" : "Miss";
        qDebug() << "Bot recieved res: " << R;
    }

    void makeTurn() {//ход бота(пока рандомный)
        Point P;
        P.x  = (uint32_t) QRandomGenerator::global()->generate() % 10;
        P.y = (uint32_t) QRandomGenerator::global()->generate() % 10;
        qDebug() << "Bot send: " << P.x << ' ' << P.y;
        emit turnMade(P);
    }

    int alive[10];
    int iteration = 0;

    FieldCell ** *ButtonField_en;

    void createField() {
        for (int i = 0; i != 10; i++)
            alive[i] = 999;

        ButtonField_en = new FieldCell**[10];
        for (int i = 0; i != 10; ++i)
            ButtonField_en[i] = new FieldCell*[10];

        for (int i = 0; i != 10; i++)
            for (int j = 0; j != 10; j++) {
                FieldCell *Btn = new FieldCell(i, j);

                ButtonField_en[i][j] = Btn;
                Btn->available = true;
                Btn->ship = false;
            }
        for(int n = 0; n < 4; n++){
            ButtonField_en[n+1][8]->ship = true;
            ButtonField_en[n+1][8]->index = iteration;
            alive[iteration] = 4;
        }
        iteration += 1;
        for(int n = 0; n < 3; n++){
            ButtonField_en[0+n][3]->ship = true;
            ButtonField_en[0+n][3]->index = iteration;
            alive[iteration] = 3;
        }
        iteration += 1;
        for(int n = 0; n < 3; n++){
            ButtonField_en[9][4+n]->ship = true;
            ButtonField_en[9][4+n]->index = iteration;
            alive[iteration] = 3;
        }
        iteration += 1;
        for(int n = 0; n < 2; n++){
            ButtonField_en[4+n][0]->ship = true;
            ButtonField_en[4+n][0]->index = iteration;
            alive[iteration] = 2;
        }
        iteration += 1;
        for(int n = 0; n < 2; n++){
            ButtonField_en[6+n][7]->ship = true;
            ButtonField_en[6+n][7]->index = iteration;
            alive[iteration] = 2;
        }
        iteration += 1;
        for(int n = 0; n < 2; n++){
            ButtonField_en[1][5+n]->ship = true;
            ButtonField_en[1][5+n]->index = iteration;
            alive[iteration] = 2;
        }
        iteration += 1;

        ButtonField_en[5][4]->ship = true;
        ButtonField_en[5][4]->index = iteration;
        alive[iteration] = 1;

        iteration += 1;

        ButtonField_en[6][9]->ship = true;
        ButtonField_en[6][9]->index = iteration;
        alive[iteration] = 1;

        iteration += 1;

        ButtonField_en[8][1]->ship = true;
        ButtonField_en[8][1]->index = iteration;
        alive[iteration] = 1;

        iteration += 1;


        ButtonField_en[9][8]->ship = true;
        ButtonField_en[9][8]->index = iteration;

        alive[iteration] = 1;

    }

};

#endif // AIPLAYER_H
