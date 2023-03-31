#ifndef INFOCHANGE_H
#define INFOCHANGE_H

#include <QDialog>
#include "UserDao.h"
#include "Model.h"
#include "mainwindow.h"

namespace Ui {
class infoChange;
}

class infoChange : public QDialog
{
    Q_OBJECT

public:
    explicit infoChange(QWidget *parent = nullptr);
    ~infoChange();
    void setUser(UserModel *u) {
        user = u;
    }
    void setInfo();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

protected:
    void closeEvent(QCloseEvent *e);
private:
    Ui::infoChange *ui;
    UserModel *user;
    MainWindow *father;
};

#endif // INFOCHANGE_H
