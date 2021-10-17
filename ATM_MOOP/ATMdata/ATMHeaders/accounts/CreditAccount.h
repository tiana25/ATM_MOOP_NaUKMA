#pragma once

#include "Account.h"

class CreditAccount : public Account {
private:
    int _creditTerm;
    double _creditDept;
    QString _creditExpiryDate;
public:
    CreditAccount();

    CreditAccount(int creditTerm, double creditDept, int userId, QString cardNumber, QString pin, QString cvv,
                  double sumOnBalance, int limit, bool isBlocked, QString expiryDate, bool isNew,
                  QString creditExpiryDate = "");

    ~CreditAccount();

    CreditAccount &operator=(const CreditAccount &);

    int &creditTerm();

    double &creditDept();

    QString &creditExpiryDate();

    const int &creditTerm() const;

    const double &creditDept() const;

    const QString &creditExpiryDate() const;


    void putMoney(double amount) override;

    void close();

    void withdrawMoney(int amount);

    void openNew(int creditTerm, double creditDept);
};
