#ifndef USERDB_H
#define USERDB_H
#pragma once

#include <QObject>
#include <QVariant>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "ATMdata/ATMHeaders/User.h"
#include "DBPath.h"

void createUser(int, QString, QString, QString);

User selectUserById(int);

User selectUserByCard(QString);

void deleteUsers(int);

#endif // USERDB_H
