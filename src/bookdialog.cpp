#include "bookdialog.h"
#include "ui_bookdialog.h"
#include "BookDao.h"
#include "FileWork.h"

bookDialog::bookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookDialog)
{
    ui->setupUi(this);
    f = (booklist*)parent;
}
void bookDialog::setInfo() {
    t = getBookById(bid);
    ui->bidLine->setText(QString::number(t.bid));
    ui->nameLine->setText(t.name);
    ui->authoLine->setText(t.autho);
    ui->pressLine->setText(t.press);
    ui->typeLine->setText(t.type);
    ui->stockLine->setText(QString::number(t.stock));
}
bookDialog::~bookDialog()
{
    delete ui;
}

void bookDialog::setAddMode() {
    ui->pushButton->setText("添加书目");
    ui->pushButton_2->setText("添加图片");
    ui->bidLine->setHidden(true);
    ui->label_2->setHidden(true);
    mod = true;
}

void bookDialog::on_pushButton_2_clicked()
{
    //photo
    if(changePhoto(this, bookPhoBaseAddr, bid)) QMessageBox::information(this, "Tip!", "Success!!");
}


void bookDialog::on_pushButton_clicked()
{
    t.stock = ui->stockLine->text().toInt();
    t.autho = ui->authoLine->text();
    t.name = ui->nameLine->text();
    t.press = ui->pressLine->text();
    t.type = ui->typeLine->text();
    if(ui->stockLine->text().length() < 1 || ui->authoLine->text().length() < 1 || ui->nameLine->text().length() < 1  || ui->pressLine->text().length() < 1) {
        QMessageBox::warning(this, "Tip!", "Invalid Input!!");
        return;
    }
    if(mod) {
        if(bookadd(&t)) {
            QMessageBox::information(this, "Tip!", "Success!!");
            this->close();
            return;
        }
        return;
    }
    if(bookUpdate(&t)) {
        QMessageBox::information(this, "Tip!", "Success!!");
        this->close();
    }
}

