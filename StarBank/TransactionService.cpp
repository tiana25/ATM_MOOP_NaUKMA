
//
// Created by Valerie Luniakina on 08.11.2020.
//

#ifndef STARBANKATM_MOOP_KMA_TRANSACTIONSERVICE_H
#define STARBANKATM_MOOP_KMA_TRANSACTIONSERVICE_H




#include <cstdio>
#include <vector>

#include "models/Transaction.h"
#include "sqlite3.h"
#include "models/accounts/CreditAccount.h"
#include "models/accounts/UniversalAccount.h"
#include "models/accounts/DepositAccount.h"

using namespace std;

//static int callbackT(void *NotUsed, int argc, char **argv, char **azColName) {
//    int i;
//    for(i = 0; i<argc; i++) {
//        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//    }
//    printf("\n");
//    return 0;
//}
/*
int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	//string data = (char *)NotUsed;
	for (i = 0; i < argc; i++) {
		queryResult += argv[i];
		queryResult += ";";
		//cout << "** " << argv[i] << endl;
	//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	//	printf("\n");
	return 0;
}*/
void createTransaction(double transactionSum, string cardSourceNumber, string cardDestinationNumber) {


	Transaction transaction(transactionSum, cardSourceNumber, cardDestinationNumber, "", 0);

	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);
	string query = "SELECT * FROM PERSON;";

	//  cout << "STATE OF TABLE BEFORE INSERT" << endl;

	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

	string transactionDateTime = transaction.transactionDateTime();

	string sql("INSERT INTO `TRANSACTION` (transaction_sum,transaction_date_time,source_account_number, destination_account_number)"
		" VALUES(" + to_string(transactionSum) + ", '" + transactionDateTime + "', '" + cardSourceNumber + "', '" + cardDestinationNumber + "');"
	);



	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}
	//  else
		  //std::cout << "Records created Successfully!" << std::endl;

	//  cout << "STATE OF TABLE AFTER INSERT" << endl;


	sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);
}


void makeTransactionFromCreditToAnother(CreditAccount& ca, string cardDest, size_t amount) {
	createTransaction(amount, ca.cardNumber(), cardDest);
	ca.withdrawMoney(amount);
}

void makeTransactionFromUniversalToAnother(UniversalAccount& ua, string cardDest, size_t amount) {
	createTransaction(amount, ua.cardNumber(), cardDest);
	ua.withdrawMoney(amount);
}

void makeTransactionFromCreditToUniversal(CreditAccount& ca, UniversalAccount& ua, size_t amount) {
	createTransaction(amount, ca.cardNumber(), ua.cardNumber());
	ca.withdrawMoney(amount);
	ua.putMoney(amount);
}

void makeTransactionFromCreditToDeposit(CreditAccount& ca, DepositAccount& da, size_t amount) {
	createTransaction(amount, ca.cardNumber(), da.cardNumber());
	ca.withdrawMoney(amount);
	da.putMoney(amount);
}

void makeTransactionFromUniversalToCredit(UniversalAccount& ua, CreditAccount& ca, size_t amount) {
	createTransaction(amount, ua.cardNumber(), ca.cardNumber());
	ca.putMoney(amount);
	ua.withdrawMoney(amount);
}

void makeTransactionFromUniversalDeposit(UniversalAccount& ua, DepositAccount& da, size_t amount) {
	createTransaction(amount, ua.cardNumber(), da.cardNumber());
	da.putMoney(amount);
	ua.withdrawMoney(amount);
}

void getAllTransactions() {
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	// cout << "STATE OF TABLE BEFORE INSERT" << endl;



	string sql("SELECT * FROM `TRANSACTION`;"
	);


	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}
	// else
	   //  std::cout << "Records created Successfully!" << std::endl;

	// cout << "STATE OF TABLE AFTER INSERT" << endl;

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);
}

void getAllTransactionsByCard(string card) {
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	// cout << "STATE OF TABLE BEFORE INSERT" << endl;



	string sql("SELECT * FROM TRANSACTION WHERE source_account_number = '" + card + "' OR destination_account_number = '" + card + "';"
	);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}
	//  else
	   //e   std::cout << "Records created Successfully!" << std::endl;

	//  cout << "STATE OF TABLE AFTER INSERT" << endl;

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);
}


#endif //STARBANKATM_MOOP_KMA_TRANSACTIONSERVICE_H