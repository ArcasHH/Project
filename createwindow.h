#ifndef CREATEWINDOW_H
#define CREATEWINDOW_H

#include <QWidget>
#include "FieldCell.h"
#include "battle.h"

namespace Ui {
class CreateWindow;
}
class QPushButton;

class CreateWindow : public QWidget
{
    Q_OBJECT

public:
    CreateWindow(QWidget *parent = nullptr);
    void generateButtons();
    ~CreateWindow();
    int num4;
    int num3;
    int num2;
    int num1;
    int iteration;
    int alive[10];

public slots:
    void buttonClicked();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_accept_clicked();
private:
    Ui::CreateWindow *ui;
    FieldCell ** *ButtonField;
    Battle *game;

};

#endif // CREATEWINDOW_H
