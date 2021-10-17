#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#pragma once

#include <QObject>
#include <QMessageBox>
#include<QMap>
#include "AccountsService.h"
#include "TransactionService.h"
#include "UserService.h"
#include "CasseteDB.h"

class SessionManager {
private:

    int _totalCashAmount;
    QMap<int, int> _notesMap;
    bool _success;

    static CreditAccount _ca;
    static UniversalAccount _ua;
    static DepositAccount _da;
    bool _cardOk = false;
    int _numTry = 0;
    static QString _card;
    static QString _pin;
    static bool _isDeposit;
    static bool _isCredit;
    static bool _isUniversal;
    static bool _cardPinOk;
    bool _limitFailure = false;
    bool _balanceFailure = false;
    bool _banknotesFailure = false;
    bool _smallAmount = false;
    bool _notEnoughMoney = false;
    bool _notDivisible = false;
    bool _isZero=false;


public:
    SessionManager() {}

    SessionManager(SessionManager &sm);

    ~SessionManager() {}

    bool has50(int x = 0) { return _notesMap[50] - x > 0; }

    bool has100(int x = 0) { return _notesMap[100] - x > 0; }

    bool has200(int x = 0) { return _notesMap[200] - x > 0; }

    bool has500(int x = 0) { return _notesMap[500] - x > 0; }

    void initialiseNotes();

    void setTotalCashAmount();

    void calculateNotesOut(int);

    void updateNotesMap(QMap<int, int>);

    void incashMoney(int);

    QMap<int, int> getNotesOut(int);

    QMap<int, int> getMap() { return _notesMap; }

    int getTotalCash() { return _totalCashAmount; }

    bool isSuccess() const { return _success; }

    bool isDeposit() const { return _isDeposit; }

    bool isCredit() { return _isCredit; }

    bool isUniversal() { return _isUniversal; }

    UniversalAccount getUniversalAccount() const { return _ua; }

    DepositAccount getDepositAccount() const { return _da; }

    CreditAccount getCreditAccount() const { return _ca; }

    QString getActiveCardNumber() const { return _card; }

    QString getPin() const { return _pin; }

    void checkCard(QString);

    void checkPin(QString);

    bool cardNumIsOk() const { return _cardOk; }

    bool cardPinIsOk() const { return _cardPinOk; }

    int getTry() { return _numTry; }

    void putMoney(int);

    void withdrawMoney(int);

    int getBalance() const;

    int getLimit() const;

    void setLimit(int);

    void putMoneyToMyCredit(int);

    void putMoneyToMyUniversal(int);

    void putMoneyToMyDeposit(int);

    void putMoneyToAnother(int, QString);

    QString getCard() { return _card; }

    QString getUser() { return (selectUserByCard(_card).firstName() + " " + selectUserByCard(_card).lastName()); }

    bool balanceFailure() { return _balanceFailure; }

    bool limitFailure() { return _limitFailure; }

    bool banknotesFailure() { return _banknotesFailure; }

    bool smallAmount() { return _smallAmount; }

    bool notEnoughMoney() { return _notEnoughMoney; }

    bool notDivisible() { return _notDivisible; }
    bool isZero(){return _isZero;}

};

#endif // SESSIONMANAGER_H

