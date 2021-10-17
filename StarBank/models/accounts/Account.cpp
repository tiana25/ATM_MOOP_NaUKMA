#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include "Account.h"

Account::Account(size_t userIdATM, string cardNumber, string pin, string cvv, double sumOnBalance, size_t limit, bool isBlocked ,
                 string expiryDate):_userId(userIdATM), _cardNumber(cardNumber), _pin(pin),
                 _cvvNumber(cvv), _sumOnBalance(sumOnBalance), _limit(limit), _isBocked(isBlocked){

    if(expiryDate.empty()){
        time_t now = time(0);
        now += 29384020;
        char* dt1 = ctime(&now);
        _expiryDate = dt1;
    }else{
        _expiryDate = expiryDate;
    }

}

Account::~Account() {}

Account& Account::operator=(const Account& account){
    _userId = account._userId;
    _cardNumber = account._cardNumber;
    _pin = account._pin;
    _expiryDate = account._expiryDate;
    _cvvNumber = account._cvvNumber;
    _limit = account._limit;
    _isBocked = account._isBocked;
    return *this;
}

size_t&  Account::userId(){
    return _userId;
}
string&  Account::cardNumber(){
    return _cardNumber;
}
string&  Account::pin(){
    return _pin;
}

string& Account::expiryDate(){
    return _expiryDate;
}

string&  Account::cvvNumber(){
    return _cvvNumber;
}
double&  Account::sumOnBalance(){
    return _sumOnBalance;
}
size_t&  Account::limit(){
    return _limit;
}

bool& Account::isBlocked(){
    return _isBocked;
}

const size_t&  Account::userId() const{
    return _userId;
}
const string&  Account::cardNumber() const{
    return _cardNumber;
}
const string&  Account::pin() const{
    return _pin;
}

const string& Account::expiryDate() const{
    return _expiryDate;
}

const string&  Account::cvvNumber() const{
    return _cvvNumber;
}
const double&  Account::sumOnBalance() const{
    return _sumOnBalance;
}
const size_t&  Account::limit() const{
    return _limit;
}

const bool& Account::isBlocked() const{
    return _isBocked;
}

ostream& operator<<(ostream& os, const Account& acc){
    os << "userID" << acc.userId() << ", cardNumber" << acc.cardNumber() << ", isBlocked? : " << acc.isBlocked() << ", ExpDate: " << acc.expiryDate() << endl;
    return os;
}