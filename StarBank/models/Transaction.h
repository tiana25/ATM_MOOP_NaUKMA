
#include <string>
#include <iostream>

using namespace std;
#ifndef STARBANKATM_MOOP_KMA_TRANSACTION_H
#define STARBANKATM_MOOP_KMA_TRANSACTION_H


class Transaction {
private:
    size_t _transactionId;
    double _transactionSum;
    string _cardSourceNumber;
    string _cardDestinationNumber;
    string _transactionDateTime;
public:

	Transaction():_transactionId(0),_transactionSum(0.0),_cardSourceNumber(""), _cardDestinationNumber(""), _transactionDateTime(""){}
    Transaction(double transactionSum, string cardSourceNumber, string cardDestinationNumber, string transactionDateTime, size_t transactionId = 0);
    ~Transaction();
    Transaction(const Transaction&);

    size_t& transactionId();
    double& transactionSum();
    string& cardSourceNumber();
    string& cardDestinationNumber();
    string& transactionDateTime();


   const size_t& transactionId() const;
   const double& transactionSum() const;
   const string& cardSourceNumber() const;
   const string& cardDestinationNumber() const;
   const string& transactionDateTime() const;
};
ostream& operator<<(ostream& os, const Transaction&);

#endif //STARBANKATM_MOOP_KMA_TRANSACTION_H
