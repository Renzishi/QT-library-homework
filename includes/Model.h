#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <iostream>
#include <ctime>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <QVariant>
#include <QDebug>

#define userPhoBaseAddr "C:\\Users\\HHS\\Desktop\\work\\images\\user\\"
#define bookPhoBaseAddr "C:\\Users\\HHS\\Desktop\\work\\images\\book\\"

using namespace std;

class Date {
public:
    int _year;
    int _month;
    int _day;
    //1900-01-01
    Date(string date) {
        _year = stoi(date.substr(0, 4));
        _month = stoi(date.substr(5, 2));
        _day = stoi(date.substr(8, 2));
    }
    Date() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        _year = 1900 + ltm->tm_year;
        _month = 1 + ltm->tm_mon;
        _day = ltm->tm_mday;
    }
    string mygetDate() {
        string s;
        s = to_string(_year) + '-' + (_month > 9 ? "" : "0") + to_string(_month) + '-' + (_day > 9 ? "" : "0") + to_string(_day);
        return s;
    }
    string addDay(int t) {
        *this += t;
        return mygetDate();
    }
    Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		return *this;
	}


	bool IsLeapyear(int year)
	{
		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}

	int GetmonthDay(int year, int month)
	{
		static int monthDay[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (IsLeapyear(year) && month == 2)
		{
			return 29;
		}
		else
		{
			return monthDay[month];
		}
	}

	bool operator==(const Date& d)
	{
		return _year == d._year
			&&_month == d._month
			&&_day == d._day;
	}

    bool operator >= (const Date& d)
    {
        return (_year*10000+_month*100+_day) >= (d._year*10000+ d._month*100+ d._day);
    }

	Date& operator+=(int day)
	{
		_day += day;
		while (_day > GetmonthDay(_year, _month))
		{
			_day =_day- GetmonthDay(_year, _month);
			_month += 1;
			if (_month > 12)
			{
				++_year;
				_month = 1;
			}
		}
			return *this;
	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
};

class BookModel {
public:
    int bid;
    QString name;
    QString autho;
    int stock;
    QString type;
    QString press;
    QString address;
    BookModel(int b, QString na, QString au, int st, QString t, QString p, QString addr) {
        bid = b;
        name = na;
        autho = au;
        stock = st;
        type = t;
        press = p;
        address = addr;
    }
    BookModel(){}
};

class UserModel {
public:
    int aid;
    QString name;
    QString account;
    int type;
    QString email;
    int max_land_num;
    QString password;
    int max_land_day;
    int credit;
    QString address;
    UserModel(int a, QString acc, QString n, QString e, int t, int mn, int md, int cr, QString addr) {
        aid = a;
        name = n;
        account = acc;
        type = t;
        email = e;
        max_land_num = mn;
        max_land_day = md;
        credit = cr;
        address = addr;
    }
    UserModel(){}

//    static bool doLogin(QString acc, QString pwd) {
//        QString sql=QString("select * from %1").arg(acc);
//        QSqlDatabase::database().transaction();
//        QSqlQuery query(sql);
//        while (query.next())
//        {
//            if(query.value(3).toString() == pwd) {
//                return true;
//            }
//        }
//        return false;
//    }
};

class HistoryModel {
public:
    int hid;
    int aid;
    int bid;
    QString bName;
    QString bAutho;
    QString beginDate;
    QString deadLine;
    bool isReturn;
    HistoryModel(int hd, int bI, int ad, QString bd, QString dl, bool ir, QString bn, QString ba) {
        hid = hd;
        aid = ad;
        bid = bI;
        beginDate = bd;
        deadLine = dl;
        isReturn = ir;
        bName = bn;
        bAutho = ba;
    }
    HistoryModel(){}
};

#endif // MODEL_H
