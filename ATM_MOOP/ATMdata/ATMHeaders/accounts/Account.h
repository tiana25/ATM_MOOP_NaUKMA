#pragma once

#include <QString>

class Account {
private:
    int _userId;
    QString _cardNumber;
    QString _pin;
    QString _expiryDate;
    QString _cvvNumber;
    int _limit;
    bool _isBocked;
    double _sumOnBalance;
public:
    Account();

    Account(int userId, QString cardNumber, QString pin, QString cvv, double sumOnBalance, int limit, bool isBlocked,
            QString expiryDate = "");

    ~Account();

    Account &operator=(const Account &);

    int &userId();

    QString &cardNumber();

    QString &pin();

    QString &expiryDate();

    QString &cvvNumber();

    double &sumOnBalance();

    int &limit();

    bool &isBlocked();

    const int &userId() const;

    const QString &cardNumber() const;

    const QString &pin() const;

    const QString &expiryDate() const;

    const QString &cvvNumber() const;

    const double &sumOnBalance() const;

    const int &limit() const;

    const bool &isBlocked() const;

    virtual void putMoney(double amount) = 0;

};
