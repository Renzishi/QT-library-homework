#include "booklist.h"
#include "ui_booklist.h"
#include "photo.h"
#include "ui_photo.h"
#include "mainwindow.h"
#include "bookdialog.h"

booklist::booklist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::booklist)
{
    ui->setupUi(this);
    connect(ui->bookTable,&QTableWidget::itemDoubleClicked,this, &booklist::selectRow);

}

void booklist::setUser(UserModel *u) {
    user = u;
    if(user->type == 0) {
        ui->addButton->setHidden(true);
        ui->fixinfo->setHidden(true);
        ui->pushButton->setHidden(true);
    }
}

void booklist::selectRow(QTableWidgetItem *item) {
    int row = item->row();
    ui->nameLine->setText(ui->bookTable->item(row, 1)->text());
    ui->authoLine->setText(ui->bookTable->item(row, 4)->text());
    ui->numLine->setText(ui->bookTable->item(row, 0)->text());
    ui->stockLine->setText(ui->bookTable->item(row, 3)->text());
}

booklist::~booklist()
{
    delete ui;
}

void booklist::flush(bool mod) {
    vector<BookModel> list;
    if(mod) {
        list = search(ui->mod->currentIndex(), ui->inputLine->text());
        ui->inputLine->clear();
    } else {
        list = getList();
    }
    int vol = list.size();
    int tmp = vol;
    while(tmp-- > 10) {
        ui->bookTable->insertRow(ui->bookTable->currentRow());
    }
    ui->bookTable->clearContents();
    for(int i = 0; i < vol; i++) {
        ui->bookTable->setItem(i,0,new QTableWidgetItem(QString::number(list[i].bid)));
        ui->bookTable->setItem(i,1,new QTableWidgetItem(list[i].name));
        ui->bookTable->setItem(i,2,new QTableWidgetItem(list[i].press));
        ui->bookTable->setItem(i,3,new QTableWidgetItem(QString::number(list[i].stock)));
        ui->bookTable->setItem(i,4,new QTableWidgetItem(list[i].autho));
        ui->bookTable->setItem(i,5,new QTableWidgetItem(list[i].type));
    }
}

void booklist::setFather(QWidget *f)
{
    father = f;
}

void booklist::closeEvent(QCloseEvent *e)
{
    father->setHidden(false);
    ((MainWindow*)father)->flush_info();
}

void booklist::on_searchButton_clicked()
{
    if(ui->inputLine->text().length() > 0) flush(true);
}


void booklist::on_flushButton_clicked()
{
    flush();
}


void booklist::on_landButton_clicked()
{
    if(user->credit < 60) {
        QMessageBox::information(this, "提示", "借阅失败\n用户信誉差！！");
        return;
    }
    if(ui->numLine->text().length() > 0 ) {
        if(landBook(ui->numLine->text().toInt(), user->aid)) {
            QMessageBox::information(this, "提示", "借阅成功");
        }
        ui->nameLine->clear();
        ui->authoLine->clear();
        ui->numLine->clear();
        ui->stockLine->clear();
        flush();
    }
}


void booklist::on_phoButton_clicked()
{
    if(ui->numLine->text().length() < 1) return;
    photo *p = new photo(this);
    p->setBackground(ui->numLine->text());
    p->exec();

}

void booklist::on_fixinfo_clicked()
{
    bookDialog *d = new bookDialog(this);
    d->setBid(ui->numLine->text().toInt());
    d->setInfo();
    d->exec();
}


void booklist::on_addButton_clicked()
{
    bookDialog *d = new bookDialog(this);
    d->setAddMode();
    d->exec();
}


void booklist::on_pushButton_clicked()
{
    if(ui->numLine->text().length() < 1) return;
    deleteBook(ui->numLine->text());
    QMessageBox::information(this, "提示", "删除成功");
    flush();
}

