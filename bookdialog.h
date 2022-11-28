#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>
#include "Model.h"
#include "booklist.h"

namespace Ui {
class bookDialog;
}

class bookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bookDialog(QWidget *parent = nullptr);
    ~bookDialog();
    void setBid(int t) {
        bid = t;
    }
    void setInfo();
    void setAddMode();
protected:
    void closeEvent(QCloseEvent *e) {
        f->flush();
    }
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::bookDialog *ui;
    int bid;
    BookModel t;
    booklist *f;
    bool mod = false;
};

#endif // BOOKDIALOG_H
