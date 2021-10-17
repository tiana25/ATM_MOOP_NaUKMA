#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include "ATMdata/ATMHeaders/Transaction.h"

Transaction::Transaction(double transactionSum, QString cardSourceNumber, QString cardDestinationNumber,
                         QString transactionDateTime, int transactionId) :
        _transactionSum(transactionSum), _cardSourceNumber(cardSourceNumber),
        _cardDestinationNumber(cardDestinationNumber) {
    if (transactionId == 0) {
        time_t now = time(0);
        char *dt = ctime(&now);
        _transactionDateTime = dt;
    } else {
        _transactionId = transactionId;
        _transactionDateTime = transactionDateTime;
    }
    return;
}

Transaction::~Transaction() {
    return;
}

int &Transaction::transactionId() {
    return _transactionId;
}

double &Transaction::transactionSum() {
    return _transactionSum;
}

QString &Transaction::cardDestinationNumber() {
    return _cardDestinationNumber;
}

QString &Transaction::cardSourceNumber() {
    return _cardSourceNumber;
}

QString &Transaction::transactionDateTime() {
    return _transactionDateTime;
}

const int &Transaction::transactionId() const {
    return _transactionId;
}

const double &Transaction::transactionSum() const {
    return _transactionSum;
}

const QString &Transaction::cardDestinationNumber() const {
    return _cardDestinationNumber;
}

const QString &Transaction::cardSourceNumber() const {
    return _cardSourceNumber;
}

const QString &Transaction::transactionDateTime() const {
    return _transactionDateTime;
}
