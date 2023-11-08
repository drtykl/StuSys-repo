#include "submenu.h"
#include "ui_submenu.h"

SubMenu::SubMenu(string title,string request,SubMenu::MeanFun fun,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);

    //窗口标题
    setFixedSize(800, 500);
    setWindowIcon(QIcon(":/Image/title.png"));
    setWindowTitle(QString::fromLocal8Bit(title.c_str()));

    //大标题
    QLabel* label = new QLabel(this);
    QFont font;
    font.setPointSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignHCenter);
    label->setText(QStringLiteral("学生信息管理系统"));
    label->setGeometry(0, 50, this->width(), 50);

    //输入要求
    ui->insert_label->setText(QString::fromLocal8Bit(request.c_str()));

    //输入模块
    ui->widget->setFixedSize(this->width() - 100, 50);
    ui->widget->setGeometry(50, 100, this->width() - 100, 50);

    //显示模块
    QTableWidget* table = new QTableWidget(this);
    table->setColumnCount(4);
    table->setFixedSize(this->width() - 100, this->height() - 250);
    table->setGeometry(50, ui->widget->height() + 130, this->width() - 50, this->height() - 100);
    table->setHorizontalHeaderLabels(QStringList() << QStringLiteral("学号") << QStringLiteral("姓名")
        << QStringLiteral("性别") << QStringLiteral("年龄"));
    
    //隐藏输入模块
    if (fun == SubMenu::ShowAll) {
        ui->widget->hide();
    }

    //显示所有
    connect(this, &SubMenu::showall, [=]() {
        std::vector<Student>stu = BasicOp::GetOp()->all_search();
        if (!stu.empty()) {
            QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("查询成功"));
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
            QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("暂无信息"));
        }
        });

    //确认按钮
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
                QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("查询成功"));
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
                QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("查询失败"));
            }
        }
            break;
        case SubMenu::NameSearch: {
            std::vector<Student>stu = BasicOp::GetOp()->name_search(text);
            if (!stu.empty()) {
                QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("查询成功"));
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
                QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("查询失败"));
            }
        }
            break;
        case SubMenu::AddStu: {
            int number = atoi(text.c_str());
            Student* stu = BasicOp::GetOp()->number_search(number);
            if (stu != nullptr) {
                QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("已存在该学号学生,信息如下"));
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
                QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("可添加该学号学生信息"));
                Student cur_stu;
                cur_stu.set_number(number);
                InsertDialog* adddialog = new InsertDialog("输入", "请输入增加学生信息", cur_stu,InsertDialog::Function::AddStu, this);
                adddialog->setAttribute(Qt::WA_DeleteOnClose);
                adddialog->exec();
            }
        }
            break;
        case SubMenu::DeleteStu: {
            int number = atoi(text.c_str());
            Student* stu = BasicOp::GetOp()->number_search(number);
            if (stu != nullptr) {
                QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("存在该学号学生,信息如下"));
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
                if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("确认"), QStringLiteral("确认删除该学生信息？"))) {
                    if (BasicOp::GetOp()->erase(number)) {
                        QMessageBox::information(this, QStringLiteral("信息"), QStringLiteral("删除成功"));
                    }
                    else {
                        QMessageBox::information(this, QStringLiteral("信息"), QStringLiteral("删除失败"));
                    }
                }
                else {
                    QMessageBox::information(this, QStringLiteral("信息"), QStringLiteral("未删除"));
                }
            }
            else {
                QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("无该学号学生信息"));
            }
        }
            break;
        case SubMenu::ModifyStu: {
            table->clearContents();
            int number = atoi(text.c_str());
            Student* stu = BasicOp::GetOp()->number_search(number);
            if (stu != nullptr) {
                QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("查询成功"));
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
                InsertDialog* modifydialog = new InsertDialog("输入", "请输入修改后学生信息", cur_stu,InsertDialog::Function::ModifyStu, this);
                modifydialog->setAttribute(Qt::WA_DeleteOnClose);
                modifydialog->exec();
            }
            else {
                QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("无该学生信息"));
            }
        }
            break;
        default:
            break;
        }
        });

    //刷新
    connect(this, &SubMenu::menuclear, [=](){
        table->clearContents();
        ui->insert_line->clear();
        });

    //返回按钮
    ui->back_ptn->resize(ui->confirm_ptn->size());
    ui->back_ptn->move(this->width() - 50 - ui->back_ptn->width(), this->height() - 50);
    connect(ui->back_ptn, &QPushButton::clicked,this,&SubMenu::backmenu);

    //显示模块

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

