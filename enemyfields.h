#ifndef ENEMYFIELDS_H
#define ENEMYFIELDS_H

#include "FieldCell.h"

class EnemyFields
{
public:
    EnemyFields();
    void generateEnemyField();
    int iteration;
    int alive[10];
private:
    FieldCell ** *ButtonField_en;
};



#endif // ENEMYFIELDS_H
