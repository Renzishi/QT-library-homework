#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include <QDialog>
#include <QTableWidgetItem>
#include "Model.h"
#include "UserDao.h"

namespace Ui {
class UserManagement;
}

class UserManagement : public QDialog
{
    Q_OBJECT

public:
    explicit UserManagement(QWidget *parent = nullptr);
    ~UserManagement();
    void flush();
private slots:
    void on_banButton_clicked();
    void selectRow(QTableWidgetItem *item);
    void on_unbanButton_clicked();

private:
    Ui::UserManagement *ui;
};

#endif // USERMANAGEMENT_H
