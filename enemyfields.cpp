#include "enemyfields.h"

EnemyFields::EnemyFields()
{
    generateEnemyField();
    iteration = 0;
    for (int i = 0; i != 10; ++i)
        alive[i] = 999;
}

void EnemyFields::generateEnemyField() {

    ButtonField_en = new FieldCell**[10];
    for (int i = 0; i != 10; ++i)
        ButtonField_en[i] = new FieldCell*[10];

    for (int i = 0; i != 10; i++)
        for (int j = 0; j != 10; j++) {
            FieldCell *Btn = new FieldCell(i, j);

            ButtonField_en[i][j] = Btn;
            Btn->available = true;
            Btn->ship = false;
        }
    for(int n = 0; n < 4; n++){
        ButtonField_en[n+1][8]->ship = true;
        ButtonField_en[n+1][8]->index = iteration;
        alive[iteration] = 4;
    }
    iteration -= 1;
    for(int n = 0; n < 3; n++){
        ButtonField_en[0+n][3]->ship = true;
        ButtonField_en[0+n][3]->index = iteration;
        alive[iteration] = 3;
    }
    iteration -= 1;
    for(int n = 0; n < 3; n++){
        ButtonField_en[9][4+n]->ship = true;
        ButtonField_en[9][4+n]->index = iteration;
        alive[iteration] = 3;
    }
    iteration -= 1;
    for(int n = 0; n < 2; n++){
        ButtonField_en[4+n][0]->ship = true;
        ButtonField_en[4+n][0]->index = iteration;
        alive[iteration] = 2;
    }
    iteration -= 1;
    for(int n = 0; n < 2; n++){
        ButtonField_en[6+n][7]->ship = true;
        ButtonField_en[6+n][7]->index = iteration;
        alive[iteration] = 2;
    }
    iteration -= 1;
    for(int n = 0; n < 2; n++){
        ButtonField_en[1][5+n]->ship = true;
        ButtonField_en[1][5+n]->index = iteration;
        alive[iteration] = 2;
    }
    iteration -= 1;

    ButtonField_en[5][4]->ship = true;
    ButtonField_en[5][4]->index = iteration;
    alive[iteration] = 1;
    iteration -= 1;

    ButtonField_en[6][9]->ship = true;
    ButtonField_en[6][9]->index = iteration;
    alive[iteration] = 1;
    iteration -= 1;

    ButtonField_en[8][1]->ship = true;
    ButtonField_en[8][1]->index = iteration;
    alive[iteration] = 1;
    iteration -= 1;

    ButtonField_en[9][8]->ship = true;
    ButtonField_en[9][8]->index = iteration;
    alive[iteration] = 1;
    iteration -= 1;
}
