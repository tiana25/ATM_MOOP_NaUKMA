#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include "CreditAccount.h"

CreditAccount::CreditAccount(size_t creditTerm, double creditDept, size_t userIdATM, string cardNumber, string pin,
                             string cvv, double sumOnBalance, size_t limit, bool isBlocked, string expiryDate,
                             string creditExpiryDate) : Account(userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,isBlocked,expiryDate),
                             _creditDept(creditDept), _creditTerm(creditTerm)
                             {
    if(creditExpiryDate.empty()){
        _sumOnBalance = creditDept;
        time_t now = time(0);
        now += creditTerm;
        char* dt1 = ctime(&now);
        _creditExpiryDate = dt1;
    }else{
        _creditExpiryDate = creditExpiryDate;
    }
}

CreditAccount::~CreditAccount(){}

CreditAccount& CreditAccount::operator=(const CreditAccount& account){
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

size_t& CreditAccount::creditTerm(){
    return _creditTerm;
}

double& CreditAccount::creditDept(){
    return _creditDept;
}

string& CreditAccount::creditExpiryDate(){
    return _creditExpiryDate;
}

const size_t& CreditAccount::creditTerm() const{
    return _creditTerm;
}

const double& CreditAccount::creditDept() const{
    return _creditDept;
}

const string& CreditAccount::creditExpiryDate() const{
    return _creditExpiryDate;
}

void CreditAccount::putMoney(double amount) {
    _creditDept -= amount;
}

void CreditAccount::withdrawMoney(size_t amount) {
    _sumOnBalance -= amount;
}

void CreditAccount::close() {
    _creditTerm = 0;
    _creditDept = 0;
    _creditExpiryDate = "";
}

void CreditAccount::openNew(size_t creditTerm, double creditDept) {
    _creditTerm = creditTerm;
    _creditDept = creditDept;
    _sumOnBalance = creditDept;

    time_t now = time(0);
    now += creditTerm;
    string dt = ctime(&now);
    _creditExpiryDate = dt;
}

ostream& operator<<(ostream& os, const CreditAccount& acc){
    os << "userID: " << acc.userId() << ", cardNumber: " << acc.cardNumber() << ", PIN: " << acc.pin() <<", CVV: " << acc.cvvNumber() << "sumOnBalance: " <<
    acc.sumOnBalance()<< ", limit: " << acc.limit() << ", isBlocked? : " << acc.isBlocked() << ", ExpDate: " << acc.expiryDate() <<
    ", creditExpiryDate: "<< acc.creditExpiryDate() << ", creditTerm: " << acc.creditTerm()<< ", creditDept: " << acc.creditDept() << endl;
    return os;
}