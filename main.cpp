#include "login.h"
#include <QApplication>

void connect_mysql();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login loginwindow;
    loginwindow.show();
    connect_mysql();
    return a.exec();
}

void connect_mysql() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("bookstore");
    db.setUserName("root");
    db.setPassword("admin");
    bool ok = db.open();
    if (!ok){
        QMessageBox::information(nullptr, "提示", "数据库连接失败");
    } else {
        qDebug() << "DB success!!";
    }
}
