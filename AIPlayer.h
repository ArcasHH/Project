#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "point.h"

#include <QObject>
#include <QRandomGenerator>
#include <QDebug>

struct AIPlayer : public QObject {
    Q_OBJECT

signals:
    void turnMade(Point);
    void turnChecked(Result);

public:

    void getTurn(Point P) {
        qDebug() << "Bot recieved move: " << P.x << ' ' << P.y;
        emit turnChecked(Result::Miss);
        makeTurn();
     }
    void getRes(Result r) {
         QString R = r == Result::Hit ? "Hit" : r == Result::Kill ? "Kill" : "Miss";
        qDebug() << "Bot recieved res: " << R;
    }

    void makeTurn() {
        Point P;
        P.x  = QRandomGenerator::global()->generate();
        P.y = QRandomGenerator::global()->generate();
        emit turnMade(P);
    }

    void createField() {
        // TODO make
    }

};

#endif // AIPLAYER_H
