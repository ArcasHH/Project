#include "recieverwindow.h"
#include "ui_recieverwindow.h"

#include "SharedDeata.h"
#include "communicator.h"
#include "createwindow.h"

#include <QtWidgets>
#include <QtNetwork>
#include <QtCore>




RecieverWindow::RecieverWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecieverWindow)
{
    ui->setupUi(this);
    prepareLayout();
}

void RecieverWindow::prepareLayout() {

    ui->StatusLabel = new QLabel(tr("Listening for broadcasted messages"));
    ui->StatusLabel->setWordWrap(true);

    auto buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(ui->QuitBtn);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(ui->StartRecieve);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(ui->StatusLabel);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Broadcast Receiver"));
}

void RecieverWindow::startListen() {
    QUdpSocket UdpS{this};
    UdpS.bind(45454, QUdpSocket::ShareAddress);

    if (!UdpS.waitForReadyRead(5000)) {
        qDebug() << "Timeout to establish connection.";
        ui->StatusLabel->setText("Timeout.");
        return;
    }

    SharedData Data;
    QHostAddress Addr;
    int Size = UdpS.readDatagram(Data.getRaw(), Data.getSize(), &Addr);
    if (Size != Data.getSize()) {
        qDebug() << "Recieved packet with size: " << Size << ". Expected: " << Data.getSize();
    }

    ui->StatusLabel->setText(tr("Received port: \"%1\" from %2. Turn: %3.")
                         .arg(Data.Port).arg(Addr.toString()).arg(Data.Turn));
    EstablishTCP(Data.Port, Addr);
    createFieldW(Data.Turn);
}

void RecieverWindow::createFieldW(int turn) {
    field = new CreateWindow(nullptr, new NetController(TcpS), turn);
    field->show();
    this->hide();
}

void RecieverWindow::EstablishTCP(int Port, QHostAddress const &Addr) {
    TcpS = new QTcpSocket(this);
    // Open connection to read/write.
    TcpS->connectToHost(Addr.toString(), Port);

}

RecieverWindow::~RecieverWindow()
{
    delete ui;
}

void RecieverWindow::on_QuitBtn_clicked()
{
    close();
}


void RecieverWindow::on_StartRecieve_clicked()
{
    startListen();
}

