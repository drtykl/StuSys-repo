#include "insertdialog.h"
#include "ui_insertdialog.h"

InsertDialog::InsertDialog(string title, string request,Student stu,InsertDialog::Function fun, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertDialog)
{
    ui->setupUi(this);

    //���ڱ���
    setFixedSize(600, 250);
    ui->widget_3->setFixedSize(600, 200);
    ui->widget_3->setGeometry(0, 0, ui->widget_3->width(), ui->widget_3->height());
    ui->dialogButtonBox->setFixedSize(300, this->height() - ui->widget_3->height());
    ui->dialogButtonBox->setGeometry(300, this->height()-ui->dialogButtonBox->height(), ui->dialogButtonBox->width(), ui->dialogButtonBox->height());
    setWindowTitle(QString::fromLocal8Bit(title.c_str()));

    //��������
    ui->request_label->setText(QString::fromLocal8Bit(request.c_str()));

    //��ʼֵ
    if (fun == InsertDialog::Function::ModifyStu) {
        ui->number_line->setText(QString::number(stu.get_number()));
        ui->name_line->setText(QString::fromLocal8Bit(stu.get_name().c_str()));
        string gender = stu.get_gender();
        if (gender == "��") {
            ui->male_rtn->setChecked(true);
        }
        else if(gender == "Ů"){
            ui->female_rtn->setChecked(true);
        }
        ui->age_box->setValue(stu.get_age());
    }
    else if (fun == InsertDialog::Function::AddStu) {
        ui->number_line->setText(QString::number(stu.get_number()));
        ui->male_rtn->setChecked(true);
    }

    //������Ϣ
    connect(ui->yes_ptn, &QPushButton::clicked, [=]() {
        if (ui->name_line->text().isEmpty() || ui->number_line->text().isEmpty()) {
            QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("����Ϊ��"));
            return;
        }
        int number = atoi(ui->number_line->text().toLatin1());
        string name = ui->name_line->text().toLocal8Bit().toStdString();
        string gender;
        if (ui->female_rtn->isChecked()) {
            gender = "��";
        }
        else if (ui->male_rtn->isChecked()) {
            gender = "Ů";
        }
        int age = ui->age_box->value();
        if (fun == InsertDialog::Function::AddStu) {
            if (BasicOp::GetOp()->add(number, name, gender, age)) {
                QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("��ӳɹ�"));
            }
            else {
                QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("���ʧ��"));
            }
        }
        else if (fun == InsertDialog::Function::ModifyStu) {
            if (BasicOp::GetOp()->modify(number, name, gender, age)) {
                QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("�޸ĳɹ�"));
            }
            else {
                QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�޸�ʧ��"));
            }
        }
        });

    //ȡ��
    connect(ui->no_ptn, &QPushButton::clicked, [=]() {
        QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("ȡ��"));
        });

    //�˳�
    connect(ui->yes_ptn, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->no_ptn, &QPushButton::clicked, this, &QDialog::close);

    
}

InsertDialog::~InsertDialog()
{
    delete ui;
}
