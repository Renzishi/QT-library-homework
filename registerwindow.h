#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QDebug>
#include "ui_registerwindow.h"
#include "Tool.h"
#include "UserDao.h"

namespace Ui {
class registerwindow;
}

class registerwindow : public QWidget
{
    Q_OBJECT

public:
    explicit registerwindow(QWidget *parent = nullptr):QWidget(parent),
    ui(new Ui::registerwindow)
    {
        ui->setupUi(this);
        setLimit(NORMAL, ui->nameIn);
        setLimit(NORMAL, ui->pwdIn);
        setLimit(EMAIL, ui->emailIn);
        setLimit(NORMAL, ui->raccIn);

        setFixedSize(360,470);
        setWindowIcon(QIcon(":/icon.ico"));
        QObject::connect(ui->backBtn, &QPushButton::clicked, this, &registerwindow::backButton_clicked);
        QObject::connect(ui->registerBtn, &QPushButton::clicked, this, &registerwindow::do_register);
    }
    ~registerwindow(){
        delete ui;
    }

public slots:
    void backButton_clicked() {
        //qDebug() << "Do_back!!";
        this->close();
    }

    void do_register() {
        if(
            doRegister(ui->raccIn->text(),
                        ui->pwdIn->text(),
                        ui->nameIn->text(),
                        ui->emailIn->text()
                        )
                ) {
            QMessageBox::information(this, "提示", "注册成功，请返回登陆");
            backButton_clicked();
        } else {
            QMessageBox::information(this, "提示", "注册失败，数据格式错误或已存在");
            ui->raccIn->clear();
            ui->pwdIn->clear();
        }
        //qDebug() << "Do_register!!";
    }

private:
    Ui::registerwindow *ui;
};

#endif // REGISTERWINDOW_H
