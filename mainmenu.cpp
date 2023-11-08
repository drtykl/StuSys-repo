#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    //���ڱ���
    setFixedSize(800, 500);
    setWindowIcon(QIcon(":/Image/title.png"));
    setWindowTitle(QStringLiteral("���˵�"));

    //�����
    QLabel* label = new QLabel(this);
    QFont font;
    font.setPointSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignHCenter);
    label->setText(QStringLiteral("ѧ����Ϣ����ϵͳ"));
    label->setGeometry(0, 50, this->width(), 50);
    
    //��ťģ��
    ui->widget_7->setFixedSize(this->width() - 50, this->height() - 250);
    ui->widget_7->setGeometry(25, 150, this->width() - 50, this->height() - 250);
    ui->widget->setStyleSheet("border-image:url(:/Image/subback.png)");
    ui->widget_2->setStyleSheet("border-image:url(:/Image/subback.png)");
    
    //���ص�½��ť
    connect(ui->logout_ptn, &QPushButton::clicked,this,&MainMenu::backlog);

    //�˳���ť
    connect(ui->close_ptn, &QPushButton::clicked,qApp,&QApplication::quit);

    //---��ʾ���а�ť---
    SubMenu* showallmenu = new SubMenu("��ʾ����", "", SubMenu::ShowAll);
    connect(ui->show_ptn, &QPushButton::clicked, [=]() {
        showallmenu->setGeometry(this->geometry());
        this->hide();
        showallmenu->show();
        });
    connect(ui->show_ptn, &QPushButton::clicked, showallmenu, &SubMenu::showall);

    //�������˵�
    connect(showallmenu, &SubMenu::backmenu, [=]() {
        if (showallmenu != nullptr) {
            showallmenu->hide();
            this->show();
        }
        });

    //---��ѧ�Ų��Ұ�ť---
    SubMenu* numbermenu = new SubMenu("ѧ�Ų���", "������ѧ��", SubMenu::NumberSearch);
    connect(ui->number_ptn, &QPushButton::clicked, [=]() {
        numbermenu->setGeometry(this->geometry());
        this->hide();
        numbermenu->show();
        });

    //����ˢ�½���
    connect(ui->number_ptn, &QPushButton::clicked, numbermenu, &SubMenu::menuclear);

    //�������˵�
    connect(numbermenu, &SubMenu::backmenu, [=]() {
        if (numbermenu != nullptr) {
            numbermenu->hide();
            this->show();
        }
        });

    //---���������Ұ�ť---
    SubMenu* namemenu = new SubMenu("��������", "����������", SubMenu::NameSearch);
    connect(ui->name_ptn, &QPushButton::clicked, [=]() {
        namemenu->setGeometry(this->geometry());
        this->hide();
        namemenu->show();
        });

    //����ˢ�½���
    connect(ui->name_ptn, &QPushButton::clicked, namemenu, &SubMenu::menuclear);

    //�������˵�
    connect(namemenu, &SubMenu::backmenu, [=]() {
        if (namemenu != nullptr) {
            namemenu->hide();
            this->show();
        }
        });

    //---���Ӱ�ť---
    SubMenu* addmenu = new SubMenu("������Ϣ", "���������Ӷ���ѧ��", SubMenu::AddStu);
    connect(ui->add_ptn, &QPushButton::clicked, [=]() {
        addmenu->setGeometry(this->geometry());
        this->hide();
        addmenu->show();
        });

    //����ˢ�½���
    connect(ui->add_ptn, &QPushButton::clicked, addmenu, &SubMenu::menuclear);

    //�������˵�
    connect(addmenu, &SubMenu::backmenu, [=]() {
        if (addmenu != nullptr) {
            addmenu->hide();
            this->show();
        }
        });

    //---ɾ����ť---
    SubMenu* deletemenu = new SubMenu("ɾ����Ϣ", "������ɾ������ѧ��", SubMenu::DeleteStu);
    connect(ui->delete_ptn, &QPushButton::clicked, [=]() {
        deletemenu->setGeometry(this->geometry());
        this->hide();
        deletemenu->show();
        });

    //����ˢ�½���
    connect(ui->delete_ptn, &QPushButton::clicked, deletemenu, &SubMenu::menuclear);

    //�������˵�
    connect(deletemenu, &SubMenu::backmenu, [=]() {
        if (deletemenu != nullptr) {
            deletemenu->hide();
            this->show();
        }
        });

    //---�޸İ�ť---
    SubMenu* modifymenu = new SubMenu("�޸���Ϣ", "�������޸Ķ���ѧ��", SubMenu::ModifyStu);
    connect(ui->modify_ptn, &QPushButton::clicked, [=]() {
        modifymenu->setGeometry(this->geometry());
        this->hide();
        modifymenu->show();
        });

    //����ˢ�½���
    connect(ui->modify_ptn, &QPushButton::clicked, modifymenu, &SubMenu::menuclear);

    //�������˵�
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
