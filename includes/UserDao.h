#ifndef USERDAO_H
#define USERDAO_H

#include "Model.h"
#include "Tool.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QVariant>

static vector<UserModel> getUserList()  {
    QString sql=QString("select * from admin where type != 1");
    vector<UserModel> tmp;
    QSqlQuery query(sql);
    while (query.next())
    {
            tmp.emplace_back(UserModel(
                                 query.value(0).toString().toInt(),
                                 query.value(1).toString(),
                                 query.value(2).toString(),
                                 query.value(4).toString(),
                                 query.value(5).toString().toInt(),
                                 query.value(6).toString().toInt(),
                                 query.value(7).toString().toInt(),
                                 query.value(8).toString().toInt(),
                                 query.value(9).toString()
                                 ));

    }
    return tmp;
}

static bool doJudge(QString acc, QString pwd) {
    if(acc.length() < 1 || pwd.length() < 1) return false;
    QString sql=QString("select * from admin where account = '%1'").arg(acc);
    QSqlQuery query(sql);
    qDebug() << sql;
    while (query.next())
    {
        qDebug() << "!";
        if(query.value(3).toString() == pwd) {
            return true;
        }
    }
    return false;
}

static UserModel* doLogin(QString acc, QString pwd) {
    qDebug() << "!";
    if(acc.length() < 1 || pwd.length() < 1) return nullptr;
    QString sql=QString("select * from admin where account = '%1'").arg(acc);
    QSqlQuery query(sql);
    qDebug() << sql;
    while (query.next())
    {
        qDebug() << "!";
        if(query.value(3).toString() == pwd) {
            return new UserModel(
                        query.value(0).toString().toInt(),
                        acc,
                        query.value(2).toString(),
                        query.value(4).toString(),
                        query.value(5).toString().toInt(),
                        query.value(6).toString().toInt(),
                        query.value(7).toString().toInt(),
                        query.value(8).toString().toInt(),
                        query.value(9).toString()
                        );
        }
    }
    return nullptr;
}

static bool doRegister(QString acc, QString pwd, QString name, QString email) {
    if(acc.length() < 1 || pwd.length() < 1 || name.length() < 1 || email.length() < 1) return false;
    QString sql=QString("select * from admin where account = '%1';").arg(acc);
    //QSqlDatabase::database().transaction();
    QSqlQuery query(sql);
    while (query.next())
    {
        return false;
    }
    QSqlQuery query2;
    sql = QString("INSERT INTO admin(`account`, `name`, `password`, `email`) VALUES ('%1', 'user-%2', md5('%3'), '%4');").arg(acc).arg(name).arg(pwd).arg(email);
    bool t = query2.exec(sql);
    if(t) {
        qDebug() << "Done";
    } else {
        qDebug() << sql;
    }

    return true;
}

static UserModel* getUserById(int aid) {
    QString sql=QString("select * from admin where aid = %1").arg(aid);
    UserModel* tmp;
    QSqlQuery query(sql);
    while (query.next())
    {
        tmp = new UserModel(
                    query.value(0).toString().toInt(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(4).toString(),
                    query.value(5).toString().toInt(),
                    query.value(6).toString().toInt(),
                    query.value(7).toString().toInt(),
                    query.value(8).toString().toInt(),
                    query.value(9).toString()
                    );
    }
    return tmp;
}

static bool changePwd(int aid, string pwd) {

    QString sql=QString("UPDATE admin SET password = '%1' WHERE aid = %2;")
            .arg(QString::fromStdString(MD5(pwd)))
            .arg(aid);
    QSqlQuery query;
    return query.exec(sql);
}

static bool changeCredit(int aid, int credit, int top) {

    QString sql=QString("UPDATE admin SET credit = %1, max_land_day = %2 WHERE aid = %3;")
            .arg(credit)
            .arg(top)
            .arg(aid);
    QSqlQuery query;
    return query.exec(sql);
}

static bool userUpdate(UserModel *tmp) {

    QString sql=QString("UPDATE admin SET name = '%1', account = '%2', email = '%3' WHERE aid = %4;")
            .arg(tmp->name)
            .arg(tmp->account)
            .arg(tmp->email)
            .arg(tmp->aid);
    qDebug() << sql;
    QSqlQuery query;
    return query.exec(sql);
}

static bool userLand(int aid, int num) {

    QString sql=QString("UPDATE admin SET max_land_num = %1 WHERE aid = %2;")
            .arg(num)
            .arg(aid);

    QSqlQuery query;
    return query.exec(sql);
}

static bool userban(int aid, int type) {

    QString sql=QString("UPDATE admin SET type = %1 WHERE aid = %2;")
            .arg(type)
            .arg(aid);

    QSqlQuery query;
    return query.exec(sql);
}

#endif // USERDAO_H
