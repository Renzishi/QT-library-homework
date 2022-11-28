#include "usermanagement.h"
#include "ui_usermanagement.h"

UserManagement::UserManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManagement)
{
    ui->setupUi(this);
    connect(ui->bookTable,&QTableWidget::itemDoubleClicked,this, &UserManagement::selectRow);
}

void UserManagement::selectRow(QTableWidgetItem *item) {
    int row = item->row();
    ui->nameLine->setText(ui->bookTable->item(row, 2)->text());
    ui->stageLine->setText(ui->bookTable->item(row, 5)->text());
    ui->numLine->setText(ui->bookTable->item(row, 0)->text());
    ui->creditLine->setText(ui->bookTable->item(row, 4)->text());
    if(ui->bookTable->item(row, 5)->text() == "活跃") {
        ui->banButton->setEnabled(true);
        ui->unbanButton->setEnabled(false);
    } else {
        ui->banButton->setEnabled(false);
        ui->unbanButton->setEnabled(true);
    }
}

void UserManagement::flush() {
    vector<UserModel> list = getUserList();

    int vol = list.size();
    ui->bookTable->clearContents();
    for(int i = 0; i < vol; i++) {
        ui->bookTable->setItem(i,0,new QTableWidgetItem(QString::number(list[i].aid)));
        ui->bookTable->setItem(i,1,new QTableWidgetItem(list[i].name));
        ui->bookTable->setItem(i,2,new QTableWidgetItem(list[i].account));
        ui->bookTable->setItem(i,3,new QTableWidgetItem(QString::number(5 - list[i].max_land_num)));
        ui->bookTable->setItem(i,4,new QTableWidgetItem(QString::number(list[i].credit)));
        ui->bookTable->setItem(i,5,new QTableWidgetItem(list[i].type == 0?"活跃":"封禁"));
    }
}

UserManagement::~UserManagement()
{
    delete ui;
}

void UserManagement::on_banButton_clicked()
{
    //禁
    userban(ui->numLine->text().toInt(), 2);
    ui->banButton->setEnabled(false);
    ui->unbanButton->setEnabled(true);
    flush();
}


void UserManagement::on_unbanButton_clicked()
{
    userban(ui->numLine->text().toInt(), 0);
    ui->banButton->setEnabled(true);
    ui->unbanButton->setEnabled(false);
    flush();
}

