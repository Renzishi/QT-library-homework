#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include "Model.h"
#include "QTableWidgetItem"
#include "BookDao.h"
#include "mainwindow.h"

namespace Ui {
class history;
}

class history : public QDialog
{
    Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr);
    ~history();
    void setUser(UserModel *tmp);
    void flush();
    void selectRow(QTableWidgetItem *item);
private slots:
    void on_phoButton_clicked();
    void on_backButton_clicked();

protected:
    void closeEvent(QCloseEvent *e)
    {
        ((MainWindow*)father)->flush_info();
    }
private:
    Ui::history *ui;
    UserModel *user;
    MainWindow* father;
};

#endif // HISTORY_H
