#include <string>
#include <iostream>
#include "../User.h"

using namespace std;
#ifndef STARBANKATM_MOOP_KMA_ACCOUNT_H
#define STARBANKATM_MOOP_KMA_ACCOUNT_H
class Account{
private:
    size_t _userId;
    string _cardNumber;
    string _pin;
    string _expiryDate;
    string _cvvNumber;
    size_t _limit;
    bool _isBocked;
protected:
    double _sumOnBalance;
public:
    class BadAmount;
    class BadPIN;
    Account(){};
    Account(size_t userIdATM, string cardNumber, string pin, string cvv, double sumOnBalance, size_t limit, bool isBlocked ,
            string expiryDate = "");
    ~Account();
    Account& operator=(const Account&);
    size_t& userId();
    string& cardNumber();
    string& pin();
    string& expiryDate();
    string& cvvNumber();
    double& sumOnBalance();
    size_t& limit();
    bool& isBlocked();

    const size_t& userId() const;
    const string& cardNumber() const;
    const string& pin() const;
    const string& expiryDate() const;
    const string& cvvNumber() const;
    const double& sumOnBalance() const;
    const size_t& limit() const;
    const bool& isBlocked() const;

    virtual void putMoney(double amount) = 0;

};
ostream& operator<<(ostream&, const Account&);

class Account::BadAmount
{
private:
    const string _reason;
    const int _number;

public:
    BadAmount(string reason, const int num)
            :_reason(reason), _number(num)
    {
        return;
    }

    ~BadAmount() { }

    void diagnose() const{
        cerr << _reason << endl;
        cerr << ' ' << _number << endl;
    }
};

class Account::BadPIN
{
private:
    const string _reason;

public:
    BadPIN(string& reason)
            :_reason(reason)
    {
        return;
    }

    ~BadPIN() { }

    inline const string& reason() const { return _reason; }
};
#endif //STARBANKATM_MOOP_KMA_ACCOUNT_H
