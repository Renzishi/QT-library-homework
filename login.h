#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QDebug>
#include "ui_login.h"
#include "registerwindow.h"
#include "mainwindow.h"
#include "Model.h"
#include "UserDao.h"
#include "Tool.h"
#include <QDebug>


namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr) :
        QWidget(parent),
        ui(new Ui::login)
    {
        ui->setupUi(this);
        setLimit(NORMAL, ui->accIn);
        setLimit(NORMAL, ui->pwdIn);
        setFixedSize(360,470);
        setWindowIcon(QIcon(":/icon.ico"));
        QObject::connect(ui->LoginBtn, &QPushButton::clicked, this, &login::loginButton_clicked);
        QObject::connect(ui->registerBtn, &QPushButton::clicked, this, &login::registerButton_clicked);
    }

    ~login()
    {
        delete ui;
    }

public slots:

    void registerButton_clicked() {
        registerwindow *rw = new registerwindow();
        rw->show();
        qDebug() << "register";
    }
    void loginButton_clicked() {
        UserModel *user = doLogin(ui->accIn->text(), QString::fromStdString(MD5(ui->pwdIn->text().toStdString())));
        //UserModel *user = new UserModel(1, "root", "administer", "123@qq.com", 1, 4, 120, 100, "def.png");
        if(user) {
            if(user->type == 2) {
                QMessageBox::information(this, "提示", "账户已被封禁");
            } else {
                QMessageBox::information(nullptr, "提示", "登录成功");
                window = new MainWindow();
                window->setUser(user);
                window->show();
                this->close();
            }
        } else {
            QMessageBox::information(nullptr, "提示", "账号或密码错误");
            ui->accIn->clear();
            ui->pwdIn->clear();
        }

        qDebug() << "login";
    }

private:
    Ui::login *ui;
    MainWindow *window;
};


#endif // LOGIN_H
