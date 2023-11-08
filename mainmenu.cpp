#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    //窗口标题
    setFixedSize(800, 500);
    setWindowIcon(QIcon(":/Image/title.png"));
    setWindowTitle(QStringLiteral("主菜单"));

    //大标题
    QLabel* label = new QLabel(this);
    QFont font;
    font.setPointSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignHCenter);
    label->setText(QStringLiteral("学生信息管理系统"));
    label->setGeometry(0, 50, this->width(), 50);
    
    //按钮模块
    ui->widget_7->setFixedSize(this->width() - 50, this->height() - 250);
    ui->widget_7->setGeometry(25, 150, this->width() - 50, this->height() - 250);
    ui->widget->setStyleSheet("border-image:url(:/Image/subback.png)");
    ui->widget_2->setStyleSheet("border-image:url(:/Image/subback.png)");
    
    //返回登陆按钮
    connect(ui->logout_ptn, &QPushButton::clicked,this,&MainMenu::backlog);

    //退出按钮
    connect(ui->close_ptn, &QPushButton::clicked,qApp,&QApplication::quit);

    //---显示所有按钮---
    SubMenu* showallmenu = new SubMenu("显示所有", "", SubMenu::ShowAll);
    connect(ui->show_ptn, &QPushButton::clicked, [=]() {
        showallmenu->setGeometry(this->geometry());
        this->hide();
        showallmenu->show();
        });
    connect(ui->show_ptn, &QPushButton::clicked, showallmenu, &SubMenu::showall);

    //返回主菜单
    connect(showallmenu, &SubMenu::backmenu, [=]() {
        if (showallmenu != nullptr) {
            showallmenu->hide();
            this->show();
        }
        });

    //---按学号查找按钮---
    SubMenu* numbermenu = new SubMenu("学号查找", "请输入学号", SubMenu::NumberSearch);
    connect(ui->number_ptn, &QPushButton::clicked, [=]() {
        numbermenu->setGeometry(this->geometry());
        this->hide();
        numbermenu->show();
        });

    //进入刷新界面
    connect(ui->number_ptn, &QPushButton::clicked, numbermenu, &SubMenu::menuclear);

    //返回主菜单
    connect(numbermenu, &SubMenu::backmenu, [=]() {
        if (numbermenu != nullptr) {
            numbermenu->hide();
            this->show();
        }
        });

    //---按姓名查找按钮---
    SubMenu* namemenu = new SubMenu("姓名查找", "请输入姓名", SubMenu::NameSearch);
    connect(ui->name_ptn, &QPushButton::clicked, [=]() {
        namemenu->setGeometry(this->geometry());
        this->hide();
        namemenu->show();
        });

    //进入刷新界面
    connect(ui->name_ptn, &QPushButton::clicked, namemenu, &SubMenu::menuclear);

    //返回主菜单
    connect(namemenu, &SubMenu::backmenu, [=]() {
        if (namemenu != nullptr) {
            namemenu->hide();
            this->show();
        }
        });

    //---增加按钮---
    SubMenu* addmenu = new SubMenu("增加信息", "请输入增加对象学号", SubMenu::AddStu);
    connect(ui->add_ptn, &QPushButton::clicked, [=]() {
        addmenu->setGeometry(this->geometry());
        this->hide();
        addmenu->show();
        });

    //进入刷新界面
    connect(ui->add_ptn, &QPushButton::clicked, addmenu, &SubMenu::menuclear);

    //返回主菜单
    connect(addmenu, &SubMenu::backmenu, [=]() {
        if (addmenu != nullptr) {
            addmenu->hide();
            this->show();
        }
        });

    //---删除按钮---
    SubMenu* deletemenu = new SubMenu("删除信息", "请输入删除对象学号", SubMenu::DeleteStu);
    connect(ui->delete_ptn, &QPushButton::clicked, [=]() {
        deletemenu->setGeometry(this->geometry());
        this->hide();
        deletemenu->show();
        });

    //进入刷新界面
    connect(ui->delete_ptn, &QPushButton::clicked, deletemenu, &SubMenu::menuclear);

    //返回主菜单
    connect(deletemenu, &SubMenu::backmenu, [=]() {
        if (deletemenu != nullptr) {
            deletemenu->hide();
            this->show();
        }
        });

    //---修改按钮---
    SubMenu* modifymenu = new SubMenu("修改信息", "请输入修改对象学号", SubMenu::ModifyStu);
    connect(ui->modify_ptn, &QPushButton::clicked, [=]() {
        modifymenu->setGeometry(this->geometry());
        this->hide();
        modifymenu->show();
        });

    //进入刷新界面
    connect(ui->modify_ptn, &QPushButton::clicked, modifymenu, &SubMenu::menuclear);

    //返回主菜单
    connect(modifymenu, &SubMenu::backmenu, [=]() {
        if (modifymenu != nullptr) {
            modifymenu->hide();
            this->show();
        }
        });
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/background.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
