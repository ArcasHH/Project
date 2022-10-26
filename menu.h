#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "createfield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    void on_pushButton_online_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_solo_clicked();

private:
    Ui::Menu *ui;
    CreateField *window;
};
#endif // MENU_H
