#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "point.h"
#include "AIPlayer.h"

#include <QThread>
#include <QTcpSocket>
#include <QObject>

struct controller : public QObject {
    Q_OBJECT
public:
    virtual void sendTurn(Point) = 0;
//    virtual bool getFeedback() = 0;
//    virtual Point recieveTurn() = 0;
    virtual void sendFeedback(Result res) = 0;
    virtual void sendFieldReady() = 0;
    virtual ~controller() {}
signals:
    void resReady(Result);
    void pReady(Point);
    void fReady();
};

struct NetController : public controller {
    Q_OBJECT
public:
    // TODO how to move it to Thread
//    QThread ExecThread;
    QTcpSocket *Connection;

    NetController(QTcpSocket *C) {
        Connection = C;
        connect(Connection, &QTcpSocket::readyRead, this, &NetController::read);
    }

public slots:
    void read() {
        Packet P;
        int Size = Connection->read(P.getRaw(), P.getSize());
        if (Size != sizeof(P)) {
            qDebug() << "Sended packet with size: " << Size << ". Expected: " << sizeof(P);
            // Retrun failure.
            return;
        }
        switch (P.PacketTy) {
            case Type::Point:
                emit pReady(P.P);
                break;
            case Type::Hit:
                emit resReady(P.Hit);
                break;
            case Type::FieldStatus:
                emit fReady();
        }
    }
public:
    void sendPacket(Packet const &P) {
        int Size = Connection->write(P.getRaw(), P.getSize());
        if (Size != P.getSize()) {
            qDebug() << "Sended packet with size: " << Size << ". Expected: " << sizeof(P);
            // Retrun failure.
        }
    }

    void sendFieldReady() override {
        sendPacket(Packet{});
    }

    void sendTurn(Point Pnt) override {
        sendPacket(Packet{Pnt});
    }

    void sendFeedback(Result res) override {
        sendPacket(Packet{res});
    }

    ~NetController() {}
};


struct AIController : public controller {
    Q_OBJECT
    AIPlayer AI;

public slots:
    void getTurn(Point P) {
        qDebug() << "Recieved move: " << P.x << P.y;
        emit pReady(P);
    }
    void getRes(Result res) {
//        qDebug() << "Recieved res: " << r;
        emit resReady(res);
    }

public:

    AIController() {
        connect(&AI, &AIPlayer::turnMade, this, &AIController::getTurn);
        connect(&AI, &AIPlayer::turnChecked, this, &AIController::getRes);
    }

    void sendTurn(Point P) override {
        AI.getTurn(P);
        return;
    }

    void sendFeedback(Result res) override {
        AI.getRes(res);
    }

    void sendFieldReady() override {
        AI.createField();
        emit fReady();
    }

    ~AIController() {}
};

#endif // COMMUNICATOR_H
