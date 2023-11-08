#ifndef SUBMENU_H
#define SUBMENU_H

#include <QWidget>
#include<Qpainter>
#include<Qicon>
#include<QLabel>
#include<Qmessagebox>
#include"BasicOp.h"
#include<Qdebug>
#include<QTableWidget>
#include"insertdialog.h"

namespace Ui {
class SubMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    enum MeanFun {
        NoneShow = 0, ShowAll, NumberSearch, NameSearch, AddStu, DeleteStu, ModifyStu
    };
    explicit SubMenu(string title,string request,SubMenu::MeanFun fun= NoneShow,QWidget *parent = nullptr);
    ~SubMenu();
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::SubMenu *ui;

signals:
    void backmenu();
    void menuclear();
    void showall();
};
 


#endif // SUBMENU_H
