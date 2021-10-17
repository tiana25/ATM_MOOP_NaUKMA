#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include "ATMdata/ATMHeaders/accounts/CreditAccount.h"

CreditAccount::CreditAccount() {}

CreditAccount::CreditAccount(int creditTerm, double creditDept, int userId, QString cardNumber, QString pin,
                             QString cvv, double sumOnBalance, int limit, bool isBlocked, QString expiryDate,
                             bool isNew,
                             QString creditExpiryDate) : Account(userId, cardNumber, pin, cvv, sumOnBalance, limit,
                                                                 isBlocked, expiryDate),
                                                         _creditDept(creditDept), _creditTerm(creditTerm) {
    if (creditExpiryDate.isEmpty() && isNew) {
        this->sumOnBalance() = creditDept;
        time_t now = time(0);
        now += creditTerm;
        char *dt1 = ctime(&now);
        _creditExpiryDate = dt1;
    } else {
        _creditExpiryDate = creditExpiryDate;
    }
}

CreditAccount::~CreditAccount() {}

CreditAccount &CreditAccount::operator=(const CreditAccount &account) {
    userId() = account.userId();
    cardNumber() = account.cardNumber();
    pin() = account.pin();
    cvvNumber() = account.cvvNumber();
    sumOnBalance() = account.sumOnBalance();
    limit() = account.limit();
    isBlocked() = account.isBlocked();
    expiryDate() = account.expiryDate();
    _creditDept = account._creditDept;
    _creditTerm = account._creditTerm;
    _creditExpiryDate = account._creditExpiryDate;
    return *this;
}

int &CreditAccount::creditTerm() {
    return _creditTerm;
}

double &CreditAccount::creditDept() {
    return _creditDept;
}

QString &CreditAccount::creditExpiryDate() {
    return _creditExpiryDate;
}

const int &CreditAccount::creditTerm() const {
    return _creditTerm;
}

const double &CreditAccount::creditDept() const {
    return _creditDept;
}

const QString &CreditAccount::creditExpiryDate() const {
    return _creditExpiryDate;
}

void CreditAccount::putMoney(double amount) {
    if (_creditDept == 0) {
        sumOnBalance() += amount;
    } else {
        double sum = _creditDept - amount;
        if (sum <= 0) {
            close();
            if (sum < 0) {
                sumOnBalance() -= sum;
            }
        } else {
            _creditDept -= amount;
        }
    }
}


void CreditAccount::withdrawMoney(int amount) {
    sumOnBalance() -= amount;
}

void CreditAccount::close() {
    _creditTerm = 0;
    _creditDept = 0;
    _creditExpiryDate = "";
}

void CreditAccount::openNew(int creditTerm, double creditDept) {
    _creditTerm = creditTerm;
    _creditDept = creditDept;
    sumOnBalance() += creditDept;

    time_t now = time(0);
    now += creditTerm;
    QString dt = ctime(&now);
    _creditExpiryDate = dt;
}

