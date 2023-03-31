#include "chpwd.h"
#include "ui_chpwd.h"
#include "QMessageBox"
#include "UserDao.h"

Chpwd::Chpwd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chpwd)
{
    ui->setupUi(this);
}

Chpwd::~Chpwd()
{
    delete ui;
}

void Chpwd::on_pushButton_clicked()
{
    if(ui->newrepeat->text().length() < 1 || ui->new_2->text().length() < 1 || ui->raw->text().length() < 1){
        QMessageBox::information(this, "提示", "输入不能为空！");
    } else if(ui->newrepeat->text() != ui->new_2->text()) {
        QMessageBox::information(this, "提示", "两次输入的密码不一致！");
        ui->newrepeat->clear();
        ui->new_2->clear();
    } else {
        if(doJudge(user->account, ui->raw->text())) {
            qDebug() << "here";
            if(changePwd(user->aid, ui->newrepeat->text().toStdString())) {
                QMessageBox::information(this, "提示", "修改成功！");
            }
        } else {
            QMessageBox::information(this, "提示", "原密码错误！");
            ui->raw->clear();
        }
    }
}

