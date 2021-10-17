#pragma once

#include <QString>

class Transaction {
private:
    int _transactionId;
    double _transactionSum;
    QString _cardSourceNumber;
    QString _cardDestinationNumber;
    QString _transactionDateTime;
public:

    Transaction(double transactionSum, QString cardSourceNumber, QString cardDestinationNumber,
                QString transactionDateTime, int transactionId = 0);

    ~Transaction();

    int &transactionId();

    double &transactionSum();

    QString &cardSourceNumber();

    QString &cardDestinationNumber();

    QString &transactionDateTime();


    const int &transactionId() const;

    const double &transactionSum() const;

    const QString &cardSourceNumber() const;

    const QString &cardDestinationNumber() const;

    const QString &transactionDateTime() const;
};
