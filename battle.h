#ifndef BATTLE_H
#define BATTLE_H

#include <QDialog>
#include "FieldCell.h"
#include "communicator.h"
//#include "createfieldwindow.h"


namespace Ui {
class Battle;
}

class Battle : public QWidget
{
    Q_OBJECT

public:
    explicit Battle(QWidget *parent, controller *control_in, int turn, FieldCell ***, int *alive_in);
    ~Battle();
    void generateEnemyField();
    void CreateYourField();
    int *alive;

public slots:
    void buttonClicked_en();

    void readRes(Result);
    void readP(Point);

private slots:
    void on_ExitButton_clicked();

private:
    Ui::Battle *ui;
    controller *control = nullptr;
    void setTurnLabel(bool turn);
    FieldCell ** *ButtonField_enemy;
    FieldCell ** *ButtonField;
   // CreateFieldWindow *field;

    int Px = 0;
    int Py = 0;
    bool win = false;
    int num_alive = 10;
    int num_killed = 0;
};

#endif // BATTLE_H
