#include "CasseteDB.h"


int get50() {
    int amount;

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    //

    QString sql("SELECT _50 FROM BANKNOTES");
    q.exec(sql);
    while (q.next()) {
        amount = q.value(0).toInt();
    }
    db.close();
    return amount;
}

int get100() {
    int amount;

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;

    QString sql("SELECT _100 FROM BANKNOTES");
    q.exec(sql);
    while (q.next()) {
        amount = q.value(0).toInt();
    }
    db.close();
    return amount;
}

int get200() {
    int amount;

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;
    QString sql("SELECT _200 FROM BANKNOTES");
    q.exec(sql);
    while (q.next()) {
        amount = q.value(0).toInt();
    }
    db.close();
    return amount;
}

int get500() {
    int amount;

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;

    QString sql("SELECT _500 FROM BANKNOTES");
    q.exec(sql);
    while (q.next()) {
        amount = q.value(0).toInt();
    }
    db.close();
    return amount;

}


void change50(int n) {

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;

    QString sql("UPDATE BANKNOTES set _50 = " + QString::number(n));
    q.exec(sql);
    db.close();
}

void change100(int n) {

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;

    QString sql("UPDATE BANKNOTES set _100 = " + QString::number(n));
    q.exec(sql);
    db.close();
}

void change200(int n) {

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;

    QString sql("UPDATE BANKNOTES set _200 = " + QString::number(n));
    q.exec(sql);
    db.close();
}

void change500(int n) {

    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();
    QSqlQuery q;

    QString sql("UPDATE BANKNOTES set _500 = " + QString::number(n));
    q.exec(sql);
    db.close();
}
