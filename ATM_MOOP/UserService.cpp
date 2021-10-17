#include "UserService.h"

User selectUserById(int idd) {
    QString sql("SELECT * FROM USER where id_user =" + QString::number(idd));
    QString firstName(""), lastName(""), middleName("");
    int id(0);
    DBPath p;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(p.getPath());
    db.open();
    QSqlQuery q;
    if (q.exec(sql)) {
        while (q.next()) {

            id = q.value(0).toInt();
            firstName = q.value(1).toString();
            lastName = q.value(2).toString();
            middleName = q.value(3).toString();
            return User(id, firstName, lastName, middleName);
        }

    } else {
        qWarning("Sql Error");
    }


    return User(id, firstName, lastName, middleName);
}

User selectUserByCard(QString card) {
    QString sql("SELECT * FROM USER WHERE id_user IN (SELECT user_id "
                "FROM CREDIT_ACCOUNT "
                "WHERE account_number=" + card + ")"
                                                 " OR id_user IN (SELECT user_id FROM DEPOSIT_ACCOUNT "
                                                 "WHERE account_number=" + card +
                ") OR id_user IN (SELECT user_id FROM UNIVERSAL_ACCOUNT WHERE account_number=" + card + ")");
    QString firstName(""), lastName(""), middleName("");
    int id(0);

    DBPath p;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(p.getPath());
    db.open();
    QSqlQuery q;

    if (q.exec(sql)) {
        while (q.next()) {
            id = q.value(0).toInt();
            firstName = q.value(1).toString();
            lastName = q.value(2).toString();
            middleName = q.value(3).toString();
            return User(id, firstName, lastName, middleName);
        }
        QMessageBox::warning(NULL, QObject::tr("Error"),
                             QObject::tr("User not found\n"), QMessageBox::Cancel);

    } else {
        qWarning("Sql Error");
    }
    db.close();
    return User(id, firstName, lastName, middleName);

}


void deleteUsers(int iduser) {
    QString sql("DELETE FROM USER WHERE id_user = " + QString::number(iduser));
    DBPath p;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(p.getPath());
    db.open();
    QSqlQuery q;
    q.exec(sql);
    db.close();
}

void createUser(int iduser, QString firstname, QString lastname, QString middlename) {
    QString sql("INSERT INTO USER (id_user,first_name,last_name,middle_name)"
                " VALUES(" + QString::number(iduser) + ", '" + firstname + "', '" + lastname + "', '" + middlename +
                "')");

    DBPath p;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(p.getPath());
    db.open();
    QSqlQuery q;
    q.exec(sql);
    db.close();
}
