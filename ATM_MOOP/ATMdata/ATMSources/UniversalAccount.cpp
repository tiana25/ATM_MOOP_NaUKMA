#include <time.h>
#include "ATMdata/ATMHeaders/accounts/UniversalAccount.h"

UniversalAccount::UniversalAccount(int userId, QString cardNumber, QString pin, QString cvv, double sumOnBalance,
                                   int limit, bool isBlocked, QString expiryDate) : Account(userId, cardNumber, pin,
                                                                                            cvv, sumOnBalance, limit,
                                                                                            isBlocked, expiryDate) {

}

UniversalAccount::UniversalAccount() {}

UniversalAccount::~UniversalAccount() {}

UniversalAccount &UniversalAccount::operator=(const UniversalAccount &account) {
    userId() = account.userId();
    cardNumber() = account.cardNumber();
    pin() = account.pin();
    cvvNumber() = account.cvvNumber();
    sumOnBalance() = account.sumOnBalance();
    limit() = account.limit();
    isBlocked() = account.isBlocked();
    expiryDate() = account.expiryDate();
    return *this;
}

void UniversalAccount::putMoney(double amount) {
    sumOnBalance() += amount;
}

void UniversalAccount::withdrawMoney(int amount) {
    sumOnBalance() -= amount;
}


