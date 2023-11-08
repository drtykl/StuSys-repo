#ifndef LOGMENU_H
#define LOGMENU_H

#include <QWidget>
#include<Qpainter>
#include<Qicon>
#include<QLabel>
#include<Qmessagebox>
#include"BasicOp.h"
#include<Qdebug>
#include"mainmenu.h"

namespace Ui {
class LogMenu;
}

class LogMenu : public QWidget
{
    Q_OBJECT

public:
    explicit LogMenu(QWidget *parent = nullptr);
    ~LogMenu();
    void paintEvent(QPaintEvent* event) override;
private:
    Ui::LogMenu *ui;

};

#endif // LOGMENU_H
