#include "photo.h"
#include "ui_photo.h"
#include "Model.h"

photo::photo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::photo)
{
    ui->setupUi(this);
}
void photo::setBackground(QString addr) {
    QImage *img=new QImage;
    QString s(bookPhoBaseAddr + addr + ".png");
    img->load(s);
    ui->headPho->resize(img->width(), img->height());
    resize(img->width(), img->height());
    ui->headPho->setPixmap(QPixmap::fromImage(*img));
}

photo::~photo()
{
    delete ui;
}
