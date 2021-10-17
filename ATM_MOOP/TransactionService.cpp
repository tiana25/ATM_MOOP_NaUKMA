
#include "TransactionService.h"
#include "AccountsService.h"

void createTransaction(int transactionSum, QString cardSourceNumber, QString cardDestinationNumber) {
    Transaction transaction(transactionSum, cardSourceNumber, cardDestinationNumber, "", 0);
    QString transactionDateTime = transaction.transactionDateTime();
    DBPath p;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(p.getPath());
    db.open();
    QSqlQuery q;
    q.exec("INSERT INTO TRANSACTION_ATM (transaction_sum,transaction_date_time,source_account_number, destination_account_number)"
           " VALUES('" + QString::number(transactionSum) + "', '" + transactionDateTime + "', '" + cardSourceNumber +
           "', '" + cardDestinationNumber + "')");
    db.close();
}

void makeTransactionFromCreditToAnother(CreditAccount &ca, QString cardDest, int amount, bool ourBankAccount) {
    createTransaction(amount, ca.cardNumber(), cardDest);
    withdrawMoneyFromCreditAccount(amount, ca);
    if (ourBankAccount) {
        putMoneyOnAccountByCard(amount, cardDest);
    }
}

void makeTransactionFromUniversalToAnother(UniversalAccount &ua, QString cardDest, int amount, bool ourBankAccount) {
    createTransaction(amount, ua.cardNumber(), cardDest);
    withdrawMoneyFromUniversalAccount(amount, ua);
    if (ourBankAccount) {
        putMoneyOnAccountByCard(amount, cardDest);
    }
}

void makeTransactionFromCreditToUniversal(CreditAccount &ca, UniversalAccount &ua, int amount) {
    createTransaction(amount, ca.cardNumber(), ua.cardNumber());
    withdrawMoneyFromCreditAccount(amount, ca);
    putMoneyOnUniversalAccount(amount, ua);
}

void makeTransactionFromCreditToDeposit(CreditAccount &ca, DepositAccount &da, int amount) {
    createTransaction(amount, ca.cardNumber(), da.cardNumber());
    withdrawMoneyFromCreditAccount(amount, ca);
    putMoneyOnDepositAccount(amount, da);
}

void makeTransactionFromUniversalToCredit(UniversalAccount &ua, CreditAccount &ca, int amount) {
    createTransaction(amount, ua.cardNumber(), ca.cardNumber());
    withdrawMoneyFromUniversalAccount(amount, ua);
    putMoneyOnCreditAccount(amount, ca);
}

void makeTransactionFromUniversalDeposit(UniversalAccount &ua, DepositAccount &da, int amount) {
    createTransaction(amount, ua.cardNumber(), da.cardNumber());
    withdrawMoneyFromUniversalAccount(amount, ua);
    putMoneyOnDepositAccount(amount, da);
}

