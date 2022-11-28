#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermanagement.h"
#include "infochange.h"
#include "history.h"
#include "chpwd.h"


MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(810, 555);
}
void MainWindow::setUser(UserModel *tmpUser) {
    user = tmpUser;
    vector<HistoryModel> tmp = getHistoryList(user->aid);
    Date d;
    int credit = user->credit;
    for(HistoryModel t : tmp) {
        if(t.isReturn == 0 && d >= Date(t.deadLine.toStdString())) {
            credit -= 10;
        }
    }
    user->max_land_day = (int)(user->max_land_day*credit*0.01);
    changeCredit(user->aid, credit, user->max_land_day);

    QImage *img=new QImage;
    img->load(userPhoBaseAddr + user->address);
    ui->headPho->setPixmap(QPixmap::fromImage(*img));
    ui->accountLine->setText(user->account);
    ui->creditLine->setText(QString::number(credit));
    ui->emailLine->setText(user->email);
    ui->landLine->setText(QString::number(user->max_land_num));
    ui->nameLine->setText(user->name);
    ui->periodLine->setText(QString::number(user->max_land_day));
    if(user->type != 1) {
        ui->userList->setHidden(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listBook_clicked()
{
    listwindow = new booklist();
    listwindow->setFather(this);
    this->setHidden(true);
    listwindow->setUser(user);
    listwindow->flush();
    listwindow->show();
}


void MainWindow::on_userList_clicked()
{
    UserManagement* win = new UserManagement(this);
    win->flush();
    win->exec();
}


void MainWindow::on_changeInfo_clicked()
{
    infoChange *window = new infoChange(this);
    window->setUser(user);
    window->setInfo();
    window->exec();
}


void MainWindow::on_landHistory_clicked()
{
    history *window = new history(this);
    window->setUser(user);
    window->flush();
    window->exec();
}

void MainWindow::flush_info()
{
    QImage *img=new QImage;
    img->load(userPhoBaseAddr + user->address);
    ui->headPho->setPixmap(QPixmap::fromImage(*img));
    ui->accountLine->setText(user->account);
    ui->creditLine->setText(QString::number(user->credit));
    ui->emailLine->setText(user->email);
    ui->landLine->setText(QString::number(user->max_land_num));
    ui->nameLine->setText(user->name);
    ui->periodLine->setText(QString::number(user->max_land_day));
}


void MainWindow::on_changePwd_clicked()
{
    Chpwd *window = new Chpwd(this);
    window->exec();
}

