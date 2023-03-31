#include "infochange.h"
#include "ui_infochange.h"
#include "FileWork.h"

infoChange::infoChange(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoChange)
{
    ui->setupUi(this);
    father = ((MainWindow*)parent);
}

infoChange::~infoChange()
{
    delete ui;
}
void infoChange::setInfo() {
    ui->accountLine->setText(user->account);
    ui->emailLine->setText(user->email);
    ui->nameLine->setText(user->name);
}
void infoChange::closeEvent(QCloseEvent *e)
{
    ((MainWindow*)father)->flush_info();
}
void infoChange::on_pushButton_clicked()
{
    user->account = ui->accountLine->text();
    user->email = ui->emailLine->text();
    user->name = ui->nameLine->text();

    if(userUpdate(user)) {
        QMessageBox::information(this, "Tip", "Success!!");
        this->close();
    } else {
        QMessageBox::information(this, "Tip", "Fault!!\nInvalid");
    }
}


void infoChange::on_pushButton_2_clicked()
{
    changePhoto(this, userPhoBaseAddr, user->aid);
    user->address = QString::fromStdString(to_string(user->aid)+".png");
}

