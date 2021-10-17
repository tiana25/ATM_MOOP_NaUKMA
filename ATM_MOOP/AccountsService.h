#ifndef DATABASE_H

#define DATABASE_H
#pragma once

#include <QObject>
#include <QVariant>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "ATMdata/ATMHeaders/accounts/CreditAccount.h"
#include "ATMdata/ATMHeaders/accounts/DepositAccount.h"
#include "ATMdata/ATMHeaders/accounts/UniversalAccount.h"
#include "DBPath.h"

void createUniversalAccount(int userIdATM, QString cardNumber, QString pin, QString cvv, double sumOnBalance,
                            int limit, QString expiryDate, bool isBlocked);

void createCreditAccount(int creditTerm, double creditDept, int userIdATM, QString cardNumber, QString pin, QString cvv,
                         double sumOnBalance, int limit, bool isBlocked, QString expiryDate,
                         QString creditExpiryDate);

void createDepositAccount(int userIdATM, QString cardNumber, QString pin, QString cvv, double sumOnBalance,
                          int limit, QString expiryDate, bool isBlocked, int depositTerm, int depositPercentage,
                          QString depositExpiryDate);

void setNewLimit(QString card, int amount);

void blockCard(QString card);

void unblockCard(QString card);

void putMoneyOnAccountByCard(double amount, QString card);

void withdrawMoneyFromUniversalAccount(int amount, UniversalAccount &ua);

void closeDeposite(DepositAccount &da);

bool creditIsValid(CreditAccount &ca);

bool depositIsValid(DepositAccount &da);

bool universalIsValid(UniversalAccount &ua);

void validateCard(QString card);

void withdrawMoneyFromCreditAccount(int amount, CreditAccount &ca);

void putMoneyOnCreditAccount(int amount, CreditAccount &ca);

void putMoneyOnUniversalAccount(int amount, UniversalAccount &ua);

void putMoneyOnDepositAccount(int amount, DepositAccount &da);

CreditAccount getCreditAccountByUserId(int id);

DepositAccount getDepositAccountByUserId(int id);

DepositAccount getDepositAccountByCardAndPin(QString card, QString pinn);

UniversalAccount getUniversalAccountByCardAndPin(QString card, QString pinn);

CreditAccount getCreditAccountByCardAndPin(QString card, QString pinn);

CreditAccount getCreditByCard(QString card);

UniversalAccount getUniversalByCard(QString card);

DepositAccount getDepositByCard(QString card);

UniversalAccount getUniversalAccountByUserId(int id);

bool cardBlocked(QString card);

bool cardExists(QString card);

#endif // DATABASE_H
