#ifndef TRANSACTIONDB_H
#define TRANSACTIONDB_H
#pragma once

#include "ATMdata/ATMHeaders/Transaction.h"
#include "ATMdata/ATMHeaders/accounts/CreditAccount.h"
#include "ATMdata/ATMHeaders/accounts/DepositAccount.h"
#include "ATMdata/ATMHeaders/accounts/UniversalAccount.h"
#include <QMessageBox>
#include "DBPath.h"

void createTransaction(int transactionSum, QString cardSourceNumber, QString cardDestinationNumber);

void makeTransactionFromCreditToAnother(CreditAccount &ca, QString cardDest, int amount, bool ourBankAccount);

void makeTransactionFromUniversalToAnother(UniversalAccount &ua, QString cardDest, int amount, bool ourBankAccount);

void makeTransactionFromCreditToUniversal(CreditAccount &ca, UniversalAccount &ua, int amount);

void makeTransactionFromCreditToDeposit(CreditAccount &ca, DepositAccount &da, int amount);

void makeTransactionFromUniversalToCredit(UniversalAccount &ua, CreditAccount &ca, int amount);

void makeTransactionFromUniversalDeposit(UniversalAccount &ua, DepositAccount &da, int amount);

#endif // TRANSACTIONDB_H
