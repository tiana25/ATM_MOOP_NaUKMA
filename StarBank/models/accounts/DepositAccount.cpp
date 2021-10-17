#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include "DepositAccount.h"



DepositAccount::DepositAccount(size_t userIdATM, string cardNumber, string pin, string cvv, double sumOnBalance,
                               size_t limit, string expiryDate, bool isBlocked,size_t depositTerm, double depositPercentage,
                                string depositExpiryDate): Account(userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,isBlocked,expiryDate){
    _depositTerm =  depositTerm;
    _depositPercentage = depositPercentage;
     if(depositExpiryDate == ""){
         time_t now = time(0);
         now+=depositTerm;
         char* dt = ctime(&now);
         depositExpiryDate = dt;
     } else{
         _depositExpiryDate = depositExpiryDate;
     }
}

DepositAccount::~DepositAccount() {

}
DepositAccount& DepositAccount::operator=(const DepositAccount& account){
    userId() = account.userId();
    cardNumber() = account.cardNumber();
    pin() = account.pin();
    cvvNumber() = account.cvvNumber();
    sumOnBalance() = account.sumOnBalance();
    limit() = account.limit();
    expiryDate() =  account.expiryDate();
    isBlocked() =  account.isBlocked();
    _depositTerm = account._depositTerm;
    _depositPercentage = account._depositPercentage;
    _depositExpiryDate = account._depositExpiryDate;
    return *this;
}

size_t& DepositAccount::depositTerm(){
    return _depositTerm;
}
string& DepositAccount::depositExpiryDate(){
    return _depositExpiryDate;
}
double& DepositAccount::depositPercentage(){
    return _depositPercentage;
}

const size_t& DepositAccount::depositTerm() const{
    return _depositTerm;
}
const string& DepositAccount::depositExpiryDate() const{
    return _depositExpiryDate;
}
const double& DepositAccount::depositPercentage() const{
    return _depositPercentage;
}

void DepositAccount::putMoney(double amount){
    _sumOnBalance += amount;
}

double DepositAccount::chargePercentageOfCost(){
    return (sumOnBalance() * depositPercentage()) / 100;
}

void DepositAccount::close(){
    _depositTerm = 0;
    _depositPercentage = 0;
    _depositExpiryDate = "";
}

void DepositAccount::openNew(size_t depositTerm, size_t depositPercentage) {
    _depositTerm = depositTerm;
    _depositPercentage = depositPercentage;

    time_t now = time(0);
    now += depositTerm;
    string dt = ctime(&now);
    _depositExpiryDate = dt;
}

ostream& operator<<(ostream& os, const DepositAccount& acc){
    os << "userID: " << acc.userId() << ", cardNumber: " << acc.cardNumber() << ", PIN: " << acc.pin() << "sumOnBalance: " <<", CVV: " << acc.cvvNumber() <<
       acc.sumOnBalance()<< ", limit: " << acc.limit() << ", isBlocked? : " << acc.isBlocked() << ", ExpDate: " << acc.expiryDate() <<
       ", depositExpiryDate: "<< acc.depositExpiryDate() << ", depositTerm: " << acc.depositTerm()<< ", depositPercentage: " << acc.depositPercentage() <<"%"<< endl;
    return os;
}