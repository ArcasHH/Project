#include "senderwindow.h"
#include "ui_senderwindow.h"

#include "SharedDeata.h"

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>

int turn = 353;

void UdpSender::run() {
    int MsgNo = 0;
    QUdpSocket UpdS{};
    SharedData Data{ListenPort, turn};

    while(Do) {
        qDebug() << "Broadcasting " + QString::number(MsgNo++);
        int Size = UpdS.writeDatagram(Data.getRaw(), Data.getSize(), QHostAddress::Broadcast, 45454);
        if (Size != Data.getSize()) {
            qDebug() << "Sended packet with size: " << Size << ". Expected: " << Data.getSize();
        }
        sleep(1);
    }
    qDebug() << "End broadcasting";
}



SenderWindow::SenderWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SenderWindow)
{
    ui->setupUi(this);
    prepareLayout();
}

void SenderWindow::prepareLayout() {
    ui->StatusLabel->setText("Ready to broadcast datagrams on port 45454");
    ui->StatusLabel->setWordWrap(true);

    setWindowTitle(tr("Broadcast Sender"));


    Listener = new QTcpServer(this);
    if (!Listener->listen()) {
        QMessageBox::critical(this, tr("Sender"),
                              tr("Unable to start the server: %1.")
                              .arg(Listener->errorString()));
        close();
        return;
    }
    connect(Listener, SIGNAL(newConnection()), this, SLOT(startListenTCP()));
    Sender = new UdpSender(this, Listener->serverPort());
}


void SenderWindow::startListenTCP() {
    TcpS = Listener->nextPendingConnection();
    if (!TcpS) {
        ui->StatusLabel->setText("Failed connection");
        return;
    }
    ui->StatusLabel->setText("New connection!");
    Sender->Do = false;

    field = new CreateField(nullptr, new NetController(TcpS), !turn);
    field->show();
    this->hide();
}

SenderWindow::~SenderWindow()
{
    Sender->Do = false;
    delete ui;
}

void SenderWindow::on_QuitBtn_clicked()
{
    close();
}

void SenderWindow::on_EmitBtn_clicked()
{
    Sender->start();
}

