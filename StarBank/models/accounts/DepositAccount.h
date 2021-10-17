#include <string>
#include <iostream>
#include "Account.h"
using namespace std;
#ifndef STARBANKATM_MOOP_KMA_DEPOSITACCOUNT_H
#define STARBANKATM_MOOP_KMA_DEPOSITACCOUNT_H

class DepositAccount : public Account{
private:
    size_t _depositTerm;
    string _depositExpiryDate;
    double _depositPercentage;
public:
    DepositAccount(){}
    DepositAccount(size_t userIdATM, string cardNumber, string pin, string cvv, double sumOnBalance,
                   size_t limit,string expiryDate,  bool isBlocked,size_t depositTerm, double depositPercentage,
                   string depositExpiryDate = "");
    ~DepositAccount();
    DepositAccount& operator=(const DepositAccount&);

    size_t& depositTerm();
    string& depositExpiryDate();
    double& depositPercentage();

    const size_t& depositTerm() const;
    const string& depositExpiryDate() const;
    const double& depositPercentage() const;

    void putMoney(double amount) override;
    double chargePercentageOfCost();
    void close();
    void openNew(size_t depositTerm, size_t depositPercentage);
};
ostream& operator<<(ostream&, const DepositAccount&);
#endif //STARBANKATM_MOOP_KMA_DEPOSITACCOUNT_H
