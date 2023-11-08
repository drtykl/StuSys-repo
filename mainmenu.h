#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include<Qpainter>
#include<Qicon>
#include<QLabel>
#include<Qmessagebox>
#include"BasicOp.h"
#include<Qdebug>
#include"submenu.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
    void paintEvent(QPaintEvent* event) override;
private:
    Ui::MainMenu *ui;
signals:
    void backlog();
};

#endif // MAINMENU_H
