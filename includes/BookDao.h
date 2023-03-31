#ifndef BOOKDAO_H
#define BOOKDAO_H

#include "Model.h"
#include "UserDao.h"
#include <vector>
using namespace std;
static vector<BookModel> getList() {
    QString sql=QString("select * from book");
    vector<BookModel> tmp;
    QSqlQuery query(sql);
    while (query.next())
    {
        tmp.emplace_back(BookModel(
                              query.value(0).toString().toInt(),
                              query.value(1).toString(),
                              query.value(2).toString(),
                              query.value(3).toString().toInt(),
                              query.value(4).toString(),
                              query.value(5).toString(),
                              query.value(6).toString())
                          );
    }
    return tmp;
}

static vector<HistoryModel> getHistoryList(int aid) {
    QString sql=QString("select * from history where aid = %1").arg(aid);
    vector<HistoryModel> tmp;
    QSqlQuery query(sql);
    while (query.next())
    {
        tmp.emplace_back(HistoryModel(
                              query.value(0).toString().toInt(),
                              query.value(1).toString().toInt(),
                              query.value(4).toString().toInt(),
                              query.value(6).toString(),
                              query.value(7).toString(),
                              (bool)query.value(5).toString().toInt(),
                              query.value(2).toString(),
                              query.value(3).toString()
                          ));
    }
    return tmp;
}

static BookModel getBookById(int bid) {
    QString sql=QString("select * from book where bid = %1").arg(bid);
    BookModel tmp;
    QSqlQuery query(sql);
    while (query.next())
    {
        tmp = BookModel(
                              query.value(0).toString().toInt(),
                              query.value(1).toString(),
                              query.value(2).toString(),
                              query.value(3).toString().toInt(),
                              query.value(4).toString(),
                              query.value(5).toString(),
                              query.value(6).toString()
                          );
    }
    return tmp;
}

static vector<BookModel> search(int cap, QString con) {
    char mod[][6] = {"name", "autho", "type"};
    QString sql=QString("select * from book where %1 like '%2%';").arg(mod[cap]).arg(con);
    vector<BookModel> tmp;
    QSqlQuery query(sql);
    while (query.next())
    {
        tmp.emplace_back(BookModel(
                              query.value(0).toString().toInt(),
                              query.value(1).toString(),
                              query.value(2).toString(),
                              query.value(3).toString().toInt(),
                              query.value(4).toString(),
                              query.value(5).toString(),
                              query.value(6).toString())
                          );
    }
    return tmp;
}

static bool bookUpdate(BookModel *tmp) {
    QString sql = QString("UPDATE book SET name = '%1', autho = '%2', stock = %3, type = '%4', press = '%5' WHERE bid = %6;").
            arg(tmp->name).
            arg(tmp->autho).
            arg(tmp->stock).
            arg(tmp->type).
            arg(tmp->press).
            arg(tmp->bid);
    QSqlQuery query;
    return query.exec(sql);
}

static bool deleteBook(QString bid) {
    QString sql = QString("delete from book WHERE bid = %1;").
            arg(bid);
    QSqlQuery query;
    qDebug() << sql;
    return query.exec(sql);
}

static bool bookadd(BookModel *tmp) {
    QString sql = QString("insert into book( `name`, `autho`, `stock`, `type`, `press`) VALUES('%1', '%2', %3, '%4', '%5');").
            arg(tmp->name).
            arg(tmp->autho).
            arg(tmp->stock).
            arg(tmp->type).
            arg(tmp->press);
    QSqlQuery query;
    return query.exec(sql);
}

static bool bookStock(int bid, int stock) {
    QString sql = QString("UPDATE book SET stock = stock +%1 WHERE bid = %2;").
            arg(stock).
            arg(bid);
    QSqlQuery query;
    return query.exec(sql);
}

static bool bookBack(QString hid) {
    QString sql = QString("UPDATE history SET isReturn = 1 WHERE hid = %2;").
            arg(hid);
    QSqlQuery query;
    return query.exec(sql);
}

static bool landBook(int bid, int aid) {
    BookModel book = getBookById(bid);
    UserModel* user = getUserById(aid);
    bookStock(bid, -1);
    user->max_land_num--;
    userLand(aid, user->max_land_num);
    Date date;
    QString sql = QString("INSERT INTO history(`bid`, `name`, `autho`, `aid`, `isReturn`, `beginDate`, `deadLine`) VALUES (%1, '%2', '%3', %4, %5, '%6', '%7');")
            .arg(bid)
            .arg(book.name)
            .arg(book.autho)
            .arg(aid)
            .arg(0)
            .arg(QString::fromStdString(date.mygetDate()))
            .arg(QString::fromStdString(date.addDay(user->max_land_day)));
    QSqlQuery query;
    return query.exec(sql);

}

#endif // BOOKDAO_H
