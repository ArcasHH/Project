#ifndef CREATEFIELD_H
#define CREATEFIELD_H

#include <QWidget>
#include "FieldCell.h"
#include "battle.h"
#include "communicator.h"

namespace Ui {
    class CreateWindow;
}
class QPushButton;

class CreateField : public QWidget
{
    Q_OBJECT

public:
    explicit CreateField(QWidget *parent, controller *c, int turn);
    ~CreateField();

    int num4;
    int num3;
    int num2;
    int num1;
    int iteration;
    int alive[10];

public slots:
    void buttonClicked();
    void generateButtons();

    void enemyFieldCreated();
    void fieldCreated();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_accept_clicked();
private:
    Ui::CreateWindow *ui;
    FieldCell ** *ButtonField;
    Battle *game;

    void checkready();

    controller *C;
    int t;
    bool My = false;
    bool En = false;

};

#endif // CREATEFIELD_H
