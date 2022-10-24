#ifndef SERVER_H
#define SERVER_H

#include <QDialog>

namespace Ui {
class Server;
}

class Server : public QDialog
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = nullptr);
    ~Server();

private slots:
    void on_back_clicked();

private:
    Ui::Server *ui;
};

#endif // SERVER_H
