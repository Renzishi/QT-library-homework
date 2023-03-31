#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "Model.h"
#include "Tool.h"
#include "booklist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setUser(UserModel *tmpUser);
    void flush_info();
private slots:
    void on_listBook_clicked();

    void on_userList_clicked();

    void on_changeInfo_clicked();

    void on_landHistory_clicked();


    void on_changePwd_clicked();

private:
    Ui::MainWindow *ui;
    UserModel *user;
    booklist *listwindow;
    QWidget *father;
};

#endif // MAINWINDOW_H
