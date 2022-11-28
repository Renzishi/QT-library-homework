#ifndef BOOKLIST_H
#define BOOKLIST_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include "BookDao.h"

namespace Ui {
class booklist;
}

class booklist : public QDialog
{
    Q_OBJECT

public:
    explicit booklist(QWidget *parent = nullptr);
    ~booklist();
    void flush(bool mod = false);
    void setFather(QWidget *f);
    void setUser(UserModel *u);
protected:
    void closeEvent(QCloseEvent *e);
public slots:
    void selectRow(QTableWidgetItem *item);
private slots:
    void on_searchButton_clicked();

    void on_flushButton_clicked();

    void on_landButton_clicked();

    void on_phoButton_clicked();

    void on_fixinfo_clicked();

    void on_addButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::booklist *ui;
    QWidget *father;
    UserModel *user;
};

#endif // BOOKLIST_H
