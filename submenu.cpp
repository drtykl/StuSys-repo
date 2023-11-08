#include "submenu.h"
#include "ui_submenu.h"

SubMenu::SubMenu(string title,string request,SubMenu::MeanFun fun,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);

    //���ڱ���
    setFixedSize(800, 500);
    setWindowIcon(QIcon(":/Image/title.png"));
    setWindowTitle(QString::fromLocal8Bit(title.c_str()));

    //�����
    QLabel* label = new QLabel(this);
    QFont font;
    font.setPointSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignHCenter);
    label->setText(QStringLiteral("ѧ����Ϣ����ϵͳ"));
    label->setGeometry(0, 50, this->width(), 50);

    //����Ҫ��
    ui->insert_label->setText(QString::fromLocal8Bit(request.c_str()));

    //����ģ��
    ui->widget->setFixedSize(this->width() - 100, 50);
    ui->widget->setGeometry(50, 100, this->width() - 100, 50);

    //��ʾģ��
    QTableWidget* table = new QTableWidget(this);
    table->setColumnCount(4);
    table->setFixedSize(this->width() - 100, this->height() - 250);
    table->setGeometry(50, ui->widget->height() + 130, this->width() - 50, this->height() - 100);
    table->setHorizontalHeaderLabels(QStringList() << QStringLiteral("ѧ��") << QStringLiteral("����")
        << QStringLiteral("�Ա�") << QStringLiteral("����"));
    
    //��������ģ��
    if (fun == SubMenu::ShowAll) {
        ui->widget->hide();
    }

    //��ʾ����
    connect(this, &SubMenu::showall, [=]() {
        std::vector<Student>stu = BasicOp::GetOp()->all_search();
        if (!stu.empty()) {
            QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("��ѯ�ɹ�"));
            int row = 0;
            table->clearContents();
            table->setRowCount(stu.size());
            for (auto& p : stu) {
                int col = 0;
                QString str;
                str = QString::number(p.get_number());
                table->setItem(row, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(p.get_name().c_str());
                table->setItem(row, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(p.get_gender().c_str());
                table->setItem(row, col++, new QTableWidgetItem(str));
                str = QString::number(p.get_age());
                table->setItem(row, col++, new QTableWidgetItem(str));
                row++;
            }
        }
        else {
            QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("������Ϣ"));
        }
        });

    //ȷ�ϰ�ť
    connect(ui->confirm_ptn, &QPushButton::clicked, [=]() {
        string text = ui->insert_line->text().toLocal8Bit().toStdString();
        switch (fun)
        {
        case SubMenu::NoneShow: 
            break;
        case SubMenu::ShowAll:
            break;
        case SubMenu::NumberSearch: {
            int number = atoi(text.c_str());
            Student* stu = BasicOp::GetOp()->number_search(number);
            if (stu != nullptr) {
                QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("��ѯ�ɹ�"));
                int col=0;
                table->clearContents();
                table->setRowCount(1);
                QString str; 
                str = QString::number(stu->get_number());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(stu->get_name().c_str());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(stu->get_gender().c_str());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::number(stu->get_age());
                table->setItem(0, col++, new QTableWidgetItem(str));
            }
            else {
                QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("��ѯʧ��"));
            }
        }
            break;
        case SubMenu::NameSearch: {
            std::vector<Student>stu = BasicOp::GetOp()->name_search(text);
            if (!stu.empty()) {
                QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("��ѯ�ɹ�"));
                int row = 0;
                table->setRowCount(stu.size());
                for (auto& p : stu) {
                    int col = 0;
                    QString str;
                    str = QString::number(p.get_number());
                    table->setItem(row, col++, new QTableWidgetItem(str));
                    str = QString::fromLocal8Bit(p.get_name().c_str());
                    table->setItem(row, col++, new QTableWidgetItem(str));
                    str = QString::fromLocal8Bit(p.get_gender().c_str());
                    table->setItem(row, col++, new QTableWidgetItem(str));
                    str = QString::number(p.get_age());
                    table->setItem(row, col++, new QTableWidgetItem(str));
                    row++;
                }
            }
            else {
                QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("��ѯʧ��"));
            }
        }
            break;
        case SubMenu::AddStu: {
            int number = atoi(text.c_str());
            Student* stu = BasicOp::GetOp()->number_search(number);
            if (stu != nullptr) {
                QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�Ѵ��ڸ�ѧ��ѧ��,��Ϣ����"));
                int col = 0;
                table->clearContents();
                table->setRowCount(1);
                QString str;
                str = QString::number(stu->get_number());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(stu->get_name().c_str());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(stu->get_gender().c_str());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::number(stu->get_age());
                table->setItem(0, col++, new QTableWidgetItem(str));
            }
            else {
                QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("����Ӹ�ѧ��ѧ����Ϣ"));
                Student cur_stu;
                cur_stu.set_number(number);
                InsertDialog* adddialog = new InsertDialog("����", "����������ѧ����Ϣ", cur_stu,InsertDialog::Function::AddStu, this);
                adddialog->setAttribute(Qt::WA_DeleteOnClose);
                adddialog->exec();
            }
        }
            break;
        case SubMenu::DeleteStu: {
            int number = atoi(text.c_str());
            Student* stu = BasicOp::GetOp()->number_search(number);
            if (stu != nullptr) {
                QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("���ڸ�ѧ��ѧ��,��Ϣ����"));
                int col = 0;
                table->clearContents();
                table->setRowCount(1);
                QString str;
                str = QString::number(stu->get_number());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(stu->get_name().c_str());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(stu->get_gender().c_str());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::number(stu->get_age());
                table->setItem(0, col++, new QTableWidgetItem(str));
                if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("ȷ��"), QStringLiteral("ȷ��ɾ����ѧ����Ϣ��"))) {
                    if (BasicOp::GetOp()->erase(number)) {
                        QMessageBox::information(this, QStringLiteral("��Ϣ"), QStringLiteral("ɾ���ɹ�"));
                    }
                    else {
                        QMessageBox::information(this, QStringLiteral("��Ϣ"), QStringLiteral("ɾ��ʧ��"));
                    }
                }
                else {
                    QMessageBox::information(this, QStringLiteral("��Ϣ"), QStringLiteral("δɾ��"));
                }
            }
            else {
                QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�޸�ѧ��ѧ����Ϣ"));
            }
        }
            break;
        case SubMenu::ModifyStu: {
            table->clearContents();
            int number = atoi(text.c_str());
            Student* stu = BasicOp::GetOp()->number_search(number);
            if (stu != nullptr) {
                QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("��ѯ�ɹ�"));
                int col = 0;
                table->setRowCount(1);
                QString str;
                str = QString::number(stu->get_number());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(stu->get_name().c_str());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::fromLocal8Bit(stu->get_gender().c_str());
                table->setItem(0, col++, new QTableWidgetItem(str));
                str = QString::number(stu->get_age());
                table->setItem(0, col++, new QTableWidgetItem(str));
                Student cur_stu(stu->get_number(), stu->get_name(), stu->get_gender(), stu->get_age());
                InsertDialog* modifydialog = new InsertDialog("����", "�������޸ĺ�ѧ����Ϣ", cur_stu,InsertDialog::Function::ModifyStu, this);
                modifydialog->setAttribute(Qt::WA_DeleteOnClose);
                modifydialog->exec();
            }
            else {
                QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�޸�ѧ����Ϣ"));
            }
        }
            break;
        default:
            break;
        }
        });

    //ˢ��
    connect(this, &SubMenu::menuclear, [=](){
        table->clearContents();
        ui->insert_line->clear();
        });

    //���ذ�ť
    ui->back_ptn->resize(ui->confirm_ptn->size());
    ui->back_ptn->move(this->width() - 50 - ui->back_ptn->width(), this->height() - 50);
    connect(ui->back_ptn, &QPushButton::clicked,this,&SubMenu::backmenu);

    //��ʾģ��

}

SubMenu::~SubMenu()
{
    delete ui;
    
}

void SubMenu::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Image/background.png");
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

