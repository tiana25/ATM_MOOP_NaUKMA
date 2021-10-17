#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include "Transaction.h"

Transaction::Transaction(double transactionSum, string cardSourceNumber, string cardDestinationNumber, string transactionDateTime, size_t transactionId):
                            _transactionSum(transactionSum), _cardSourceNumber(cardSourceNumber), _cardDestinationNumber(cardDestinationNumber){
    if(transactionId == 0){
        time_t now = time(0);
        char* dt = ctime(&now);
        _transactionDateTime = dt;
    }else{
        _transactionId = transactionId;
        _transactionDateTime = transactionDateTime;
    }
    return;
}

Transaction::~Transaction() {
    return;
}
Transaction::Transaction(const Transaction& t): _transactionId(t._transactionId),
_transactionDateTime(t._transactionDateTime), _transactionSum(t._transactionSum),
_cardSourceNumber(t._cardSourceNumber), _cardDestinationNumber(t._cardDestinationNumber){
    _transactionSum = t._transactionSum;
    _cardSourceNumber = t._cardSourceNumber;
    _cardDestinationNumber = t._cardDestinationNumber;
    _transactionId = t._transactionId;
    _transactionDateTime = t._transactionDateTime;
}

size_t& Transaction::transactionId() {
    return _transactionId;
}

double& Transaction::transactionSum() {
    return _transactionSum;
}

string& Transaction::cardDestinationNumber() {
    return _cardDestinationNumber;
}

string& Transaction::cardSourceNumber() {
    return _cardSourceNumber;
}

string& Transaction::transactionDateTime() {
    return _transactionDateTime;
}






const size_t& Transaction::transactionId() const{
    return _transactionId;
}

const double& Transaction::transactionSum() const{
    return _transactionSum;
}

const string& Transaction::cardDestinationNumber() const{
    return _cardDestinationNumber;
}

const string& Transaction::cardSourceNumber() const{
    return _cardSourceNumber;
}

const string& Transaction::transactionDateTime() const{
    return _transactionDateTime;
}

ostream& operator<<(ostream& os, const Transaction& t) {
	os << "ID: " << t.transactionId() << " Sum: " << t.transactionSum() << " Date: " << t.transactionDateTime() << " From: " << t.cardSourceNumber() << " To: "<< t.cardDestinationNumber() << endl;
	return os;
}