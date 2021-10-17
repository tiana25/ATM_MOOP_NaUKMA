
#ifndef STARBANKATM_MOOP_KMA_TRANSACTIONSERVICE_H
#define STARBANKATM_MOOP_KMA_TRANSACTIONSERVICE_H


#include "../models/Transaction.h"
#include <cstdio>
#include "../sqlite3.h"
#include <vector>
#include "AccountService.h"
#include <list>

void createTransaction(double transactionSum, string cardSourceNumber, string cardDestinationNumber){


    Transaction transaction(transactionSum,cardSourceNumber,cardDestinationNumber,"",0);

    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);
    string query = "SELECT * FROM PERSON;";

    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    string transactionDateTime = transaction.transactionDateTime();

    string sql("INSERT INTO `TRANSACTION` (transaction_sum,transaction_date_time,source_account_number, destination_account_number)"
               " VALUES("  + to_string(transactionSum) + ", '" + transactionDateTime + "', '" + cardSourceNumber + "', '"+ cardDestinationNumber + "');"
    );



    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }


    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
}

void makeTransactionFromCreditToAnother(CreditAccount& ca, string cardDest, size_t amount, bool ourBankAccount) {
	createTransaction(amount, ca.cardNumber(), cardDest);
	withdrawMoneyFromCreditAccount(amount, ca);
	if (ourBankAccount) {
		putMoneyOnAccountByCard(amount, cardDest);
	}
}

void makeTransactionFromUniversalToAnother(UniversalAccount& ua, string cardDest, size_t amount, bool ourBankAccount) {
	createTransaction(amount, ua.cardNumber(), cardDest);
	withdrawMoneyFromUniversalAccount(amount, ua);
	if (ourBankAccount) {
		putMoneyOnAccountByCard(amount, cardDest);
	}
}

void makeTransactionFromCreditToUniversal(CreditAccount& ca, UniversalAccount& ua, size_t amount) {
	createTransaction(amount, ca.cardNumber(), ua.cardNumber());
	withdrawMoneyFromCreditAccount(amount, ca);
	putMoneyOnUniversalAccount(amount, ua);
}

void makeTransactionFromCreditToDeposit(CreditAccount& ca, DepositAccount& da, size_t amount) {
	createTransaction(amount, ca.cardNumber(), da.cardNumber());
	withdrawMoneyFromCreditAccount(amount, ca);
	putMoneyOnDepositAccount(amount, da);
}

void makeTransactionFromUniversalToCredit(UniversalAccount& ua, CreditAccount& ca, size_t amount) {
	createTransaction(amount, ua.cardNumber(), ca.cardNumber());
	withdrawMoneyFromUniversalAccount(amount, ua);
	putMoneyOnCreditAccount(amount, ca);
}

void makeTransactionFromUniversalToDeposit(UniversalAccount& ua, DepositAccount& da, size_t amount) {
	createTransaction(amount, ua.cardNumber(), da.cardNumber());
	withdrawMoneyFromUniversalAccount(amount, ua);
	putMoneyOnDepositAccount(amount, da);
}


list<Transaction> getAllTransactionsByCard(string card){
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);

    string sql("SELECT * FROM `TRANSACTION` WHERE `source_account_number` = '" + card + "' OR `destination_account_number` = '" + card +"';"
    );

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	list<Transaction> res;
	if (queryResult != "") {

		string sourceAccountNumber, destAccountNumber, transDate;
		int id(0), sum(0);
		std::string delimiter = ";";
		size_t pos = 0;
		std::string token;
		int j = 0;
		while ((pos = queryResult.find(delimiter)) != std::string::npos) {
			token = queryResult.substr(0, pos);
			switch (j) {
			case 0:
				id = stoi(token);
				j++;
				break;
			case 1:
				sum = stoi(token);
				j++;
				break;
			case 2:
				transDate = token;
				j++;
				break;
			case 3:
				sourceAccountNumber = token;
				j++;
				break;
			case 4:
				destAccountNumber = token;
				if (queryResult != token + ";") {
					j = 0;
					
				}
				else {
					j++;
				}
				res.push_back(Transaction(sum, sourceAccountNumber, destAccountNumber, transDate, id));
				break;
			}

			queryResult.erase(0, pos + delimiter.length());
		}
		queryResult = "";
		
		sqlite3_close(DB);
		

	}
	sqlite3_close(DB);
	return res;
}


#endif //STARBANKATM_MOOP_KMA_TRANSACTIONSERVICE_H