#pragma once

#include "Account.h"

class DepositAccount : public Account {
private:
    int _depositTerm;
    QString _depositExpiryDate;
    double _depositPercentage;
public:
    DepositAccount();

    DepositAccount(int userId, QString cardNumber, QString pin, QString cvv, double sumOnBalance,
                   int limit, QString expiryDate, bool isBlocked, int depositTerm, double depositPercentage, bool isNew,
                   QString depositExpiryDate = "");

    ~DepositAccount();

    DepositAccount &operator=(const DepositAccount &);

    int &depositTerm();

    QString &depositExpiryDate();

    double &depositPercentage();

    const int &depositTerm() const;

    const QString &depositExpiryDate() const;

    const double &depositPercentage() const;

    void putMoney(double amount) override;

    double chargePercentageOfCost();

    void close();

    void openNew(int depTerm, double sum, double percentage);
};
