#pragma once

#include "Account.h"

class UniversalAccount : public Account {

public:
    UniversalAccount();

    UniversalAccount(int userId, QString cardNumber, QString pin, QString cvv, double sumOnBalance,
                     int limit, bool isBlocked, QString expiryDate);

    ~UniversalAccount();

    UniversalAccount &operator=(const UniversalAccount &);

    void putMoney(double amount) override;

    void withdrawMoney(int amount);
};
