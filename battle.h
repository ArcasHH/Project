#ifndef BATTLE_H
#define BATTLE_H

#include <QDialog>
#include "FieldCell.h"
//#include "createfieldwindow.h"


namespace Ui {
class Battle;
}

class Battle : public QWidget
{
    Q_OBJECT

public:
    explicit Battle(QWidget *parent, FieldCell ***Field, int *ptr);
    ~Battle();
    void generateEnemyField();
    void CreateYourField();
    int alive[10];

public slots:
    void buttonClicked_en();

private:
    Ui::Battle *ui;
    FieldCell ** *ButtonField_enemy;
    FieldCell ** *ButtonField;
   // CreateFieldWindow *field;
};

#endif // BATTLE_H
