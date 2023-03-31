#ifndef CHPWD_H
#define CHPWD_H

#include <QDialog>
#include "Model.h"

namespace Ui {
class Chpwd;
}

class Chpwd : public QDialog
{
    Q_OBJECT

public:
    explicit Chpwd(QWidget *parent = nullptr);
    ~Chpwd();
    void setUser(UserModel *u) {
        user = u;
    }
private slots:
    void on_pushButton_clicked();

private:
    Ui::Chpwd *ui;
    UserModel *user;
};

#endif // CHPWD_H
