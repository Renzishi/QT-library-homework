#ifndef FILEWORK_H
#define FILEWORK_H

#include <QFileDialog>
#include <QMessageBox>
#include <QWidget>

static bool changePhoto(QWidget* obj, QString baseAddr, int id) {
    QString fileName = QFileDialog::getOpenFileName(
            obj,
            "open a image.",
            "C:/",
            "images(*.png)");
    if (fileName.isEmpty()) {
        QMessageBox::warning(obj, "Warning!", "Invalid file!!");
    }
    QString name = QString::number(id);
    QFile file(baseAddr + name + ".png");
    file.remove();
    bool ok = QFile::copy(fileName, baseAddr + name + ".png");
    return ok;
}

#endif // FILEWORK_H
