#include "logmenu.h"
#include "ui_logmenu.h"

LogMenu::LogMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogMenu)
{
    ui->setupUi(this);

    //���ڱ���
    setFixedSize(800, 500);
    setWindowIcon(QIcon(":/Image/title.png"));
    setWindowTitle(QStringLiteral("��¼����"));

    //�����
    QLabel* label = new QLabel(this);
    QFont font;
    font.setPointSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignHCenter);
    label->setText(QStringLiteral("ѧ����Ϣ����ϵͳ"));
    label->setGeometry(0, 50, this->width(), 50);

    //��¼���
    ui->widget_3->setFixedSize(this->width() / 2 - 50, this->height() - 250);
    ui->widget_3->setGeometry(this->width() / 2, 150, this->width() / 2 - 50, this->height() - 250);

    //��¼��ť
    MainMenu* mainmenu = new MainMenu();
    connect(ui->log_btn, &QPushButton::clicked, [=]() {
        string account_text = ui->account_line->text().toLocal8Bit().toStdString();
        string password_text = ui->password_line->text().toLocal8Bit().toStdString();
        //��֤����
        if (BasicOp::GetOp()->login(account_text, password_text)){
            QMessageBox::information(this, QStringLiteral("��¼��Ϣ"), QStringLiteral("��¼�ɹ�"));
            mainmenu->setGeometry(this->geometry());
            this->hide();
            mainmenu->show();
            ui->account_line->clear();
            ui->password_line->clear();
        }
        else {
            QMessageBox::information(this, QStringLiteral("��¼��Ϣ"), QStringLiteral("��¼ʧ��"));
        }
        });

    //���ص�½����
    connect(mainmenu, &MainMenu::backlog, [=]() {
        mainmenu->hide();
        this->show();
        });

    //�˳���ť
    connect(ui->quit_btn, &QPushButton::clicked, this, [=]() {
        BasicOp::DeleteOp();
        this->close();
        });
}

LogMenu::~LogMenu()
{
    delete ui;
}

void LogMenu::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/logback.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
