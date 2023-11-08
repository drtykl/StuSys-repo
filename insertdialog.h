#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>
#include"BasicOp.h"
#include<QMessageBox>

namespace Ui {
class InsertDialog;
}

class InsertDialog : public QDialog
{
    Q_OBJECT

public:
    enum Function {
        None = 0, AddStu, ModifyStu
    };
    explicit InsertDialog(string title, string request, Student stu, InsertDialog::Function fun=InsertDialog::Function::None, QWidget* parent = nullptr);
    ~InsertDialog();

private:
    Ui::InsertDialog *ui;
};

#endif // INSERTDIALOG_H
