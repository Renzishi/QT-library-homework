#include "history.h"
#include "ui_history.h"
#include "photo.h"

history::history(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::history)
{
    ui->setupUi(this);
    connect(ui->bookTable,&QTableWidget::itemDoubleClicked,this, &history::selectRow);
    ui->bidLab->setHidden(true);
    ui->backButton->setEnabled(false);
    father = (MainWindow*)parent;
}

void history::selectRow(QTableWidgetItem *item) {
    int row = item->row();
    ui->nameLine->setText(ui->bookTable->item(row, 2)->text());
    ui->beginLine->setText(ui->bookTable->item(row, 3)->text());
    ui->numLine->setText(ui->bookTable->item(row, 0)->text());
    ui->backLine->setText(ui->bookTable->item(row, 4)->text());
    ui->bidLab->setText(ui->bookTable->item(row, 1)->text());
    if(ui->bookTable->item(row, 5)->text() == "已归还") {
        ui->backButton->setEnabled(false);
    } else {
        ui->backButton->setEnabled(true);
    }
}

history::~history()
{
    delete ui;
}

void history::setUser(UserModel *tmp)
{
    user = tmp;
}

void history::flush() {
    vector<HistoryModel> list = getHistoryList(user->aid);
    int vol = list.size();
    ui->bookTable->clearContents();
    for(int i = 0; i < vol; i++) {
        ui->bookTable->setItem(i,0,new QTableWidgetItem(QString::number(list[i].hid)));
        ui->bookTable->setItem(i,1,new QTableWidgetItem(QString::number(list[i].bid)));
        ui->bookTable->setItem(i,2,new QTableWidgetItem(list[i].bName));
        ui->bookTable->setItem(i,3,new QTableWidgetItem(list[i].beginDate));
        ui->bookTable->setItem(i,4,new QTableWidgetItem(list[i].deadLine));
        ui->bookTable->setItem(i,5,new QTableWidgetItem(list[i].isReturn?"已归还":"借阅中"));
    }
}

void history::on_phoButton_clicked()
{
    photo *p = new photo();
    p->setBackground(ui->bidLab->text());
    p->exec();
}


void history::on_backButton_clicked()
{
    int credit = user->credit;
    Date d;
    if(d >= Date(ui->backLine->text().toStdString())) {
        credit += 5;
    } else {
        credit += 1;
    }
    bookBack(ui->numLine->text());
    user->credit = credit;
    user->max_land_num++;
    userLand(user->aid, user->max_land_num);
    bookStock(ui->bidLab->text().toInt(), 1);
    ui->nameLine->clear();
    ui->beginLine->clear();
    ui->numLine->clear();
    ui->backLine->clear();
    ui->bidLab->clear();
    flush();
}

