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
    explicit Battle(QWidget *parent, controller *control_in, int turn, FieldCell ***);
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
    void setTurnLabel(int turn);
    FieldCell ** *ButtonField_enemy;
    FieldCell ** *ButtonField;
   // CreateFieldWindow *field;
};

#endif // BATTLE_H
