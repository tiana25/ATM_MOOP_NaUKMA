#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include "ATMdata/ATMHeaders/accounts/DepositAccount.h"

DepositAccount::DepositAccount() {}

DepositAccount::DepositAccount(int userId, QString cardNumber, QString pin, QString cvv, double sumOnBalance,
                               int limit, QString expiryDate, bool isBlocked, int depositTerm, double depositPercentage,
                               bool isNew,
                               QString depositExpiryDate) : Account(userId, cardNumber, pin, cvv, sumOnBalance, limit,
                                                                    isBlocked, expiryDate) {
    _depositTerm = depositTerm;
    _depositPercentage = depositPercentage;
    if (depositExpiryDate == "" && isNew) {
        time_t now = time(0);
        now += depositTerm;
        char *dt = ctime(&now);
        _depositExpiryDate = dt;
    } else {
        _depositExpiryDate = depositExpiryDate;
    }
}

DepositAccount::~DepositAccount() {

}

DepositAccount &DepositAccount::operator=(const DepositAccount &account) {
    userId() = account.userId();
    cardNumber() = account.cardNumber();
    pin() = account.pin();
    cvvNumber() = account.cvvNumber();
    sumOnBalance() = account.sumOnBalance();
    limit() = account.limit();
    expiryDate() = account.expiryDate();
    isBlocked() = account.isBlocked();
    _depositTerm = account._depositTerm;
    _depositPercentage = account._depositPercentage;
    _depositExpiryDate = account._depositExpiryDate;
    return *this;
}

int &DepositAccount::depositTerm() {
    return _depositTerm;
}

QString &DepositAccount::depositExpiryDate() {
    return _depositExpiryDate;
}

double &DepositAccount::depositPercentage() {
    return _depositPercentage;
}

const int &DepositAccount::depositTerm() const {
    return _depositTerm;
}

const QString &DepositAccount::depositExpiryDate() const {
    return _depositExpiryDate;
}

const double &DepositAccount::depositPercentage() const {
    return _depositPercentage;
}

void DepositAccount::putMoney(double amount) {
    sumOnBalance() += amount;
}

double DepositAccount::chargePercentageOfCost() {
    return (sumOnBalance() * depositPercentage()) / 100;
}

void DepositAccount::close() {
    _depositTerm = 0;
    _depositPercentage = 0;
    _depositExpiryDate = "";
}

void DepositAccount::openNew(int depTerm, double sum, double percentage) {
    _depositTerm = depTerm;
    _depositPercentage = percentage;
    sumOnBalance() += sum;

    time_t now = time(0);
    now += depTerm;
    QString dt = ctime(&now);
    _depositExpiryDate = dt;
}


