#include <time.h>
#include "UniversalAccount.h"



UniversalAccount::UniversalAccount(size_t userIdATM, string cardNumber, string pin, string cvv, double sumOnBalance,
        size_t limit,  bool isBlocked,string expiryDate):Account(userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,isBlocked,expiryDate){

}

UniversalAccount::~UniversalAccount(){}

UniversalAccount& UniversalAccount::operator=(const UniversalAccount& account){
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
       _sumOnBalance += amount;
}

void UniversalAccount::withdrawMoney(size_t amount){
    _sumOnBalance -= amount;
}

ostream& operator<<(ostream& os, const UniversalAccount& acc){
    os << "userID" << acc.userId() << ", cardNumber" << acc.cardNumber() << ", PIN: " << acc.pin() <<", CVV: " << acc.cvvNumber() <<
    "sumOnBalance: " << acc.sumOnBalance()<< ", limit: " << acc.limit() << ", isBlocked? : " << acc.isBlocked() << ", ExpDate: " <<
    acc.expiryDate() << endl;
    return os;
}