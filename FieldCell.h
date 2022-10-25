#ifndef FIELDCELL_H
#define FIELDCELL_H

#include <QPushButton>

struct FieldCell : public QPushButton {
    int x;
    int y;
    bool available = true;
    bool ship = false;
    int index;
public:
    FieldCell(int x_in, int y_in) : x{x_in}, y{y_in} {}
};



#endif // FIELDCELL_H
