#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include "ATMdata/ATMHeaders/accounts/Account.h"

Account::Account() {

}

Account::Account(int userId, QString cardNumber, QString pin, QString cvv, double sumOnBalance, int limit,
                 bool isBlocked,
                 QString expiryDate) : _userId(userId), _cardNumber(cardNumber), _pin(pin),
                                       _cvvNumber(cvv), _sumOnBalance(sumOnBalance), _limit(limit),
                                       _isBocked(isBlocked) {

    if (expiryDate.isEmpty()) {
        time_t now = time(0);
        now += 29384020;
        char *dt1 = ctime(&now);
        _expiryDate = dt1;
    } else {
        _expiryDate = expiryDate;
    }

}

Account::~Account() {}

Account &Account::operator=(const Account &account) {
    _userId = account._userId;
    _cardNumber = account._cardNumber;
    _pin = account._pin;
    _expiryDate = account._expiryDate;
    _cvvNumber = account._cvvNumber;
    _limit = account._limit;
    _isBocked = account._isBocked;
    return *this;
}

int &Account::userId() {
    return _userId;
}

QString &Account::cardNumber() {
    return _cardNumber;
}

QString &Account::pin() {
    return _pin;
}

QString &Account::expiryDate() {
    return _expiryDate;
}

QString &Account::cvvNumber() {
    return _cvvNumber;
}

double &Account::sumOnBalance() {
    return _sumOnBalance;
}

int &Account::limit() {
    return _limit;
}

bool &Account::isBlocked() {
    return _isBocked;
}

const int &Account::userId() const {
    return _userId;
}

const QString &Account::cardNumber() const {
    return _cardNumber;
}

const QString &Account::pin() const {
    return _pin;
}

const QString &Account::expiryDate() const {
    return _expiryDate;
}

const QString &Account::cvvNumber() const {
    return _cvvNumber;
}

const double &Account::sumOnBalance() const {
    return _sumOnBalance;
}

const int &Account::limit() const {
    return _limit;
}

const bool &Account::isBlocked() const {
    return _isBocked;
}


