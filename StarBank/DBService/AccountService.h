#ifndef STARBANKATM_MOOP_KMA_ACCOUNTSERVICE_H
#define STARBANKATM_MOOP_KMA_ACCOUNTSERVICE_H
#include "../models/accounts/Account.h"
#include "../models/accounts/CreditAccount.h"
#include "../models/accounts/DepositAccount.h"
#include "../models/accounts/UniversalAccount.h"
#include <cstdio>
#include "../sqlite3.h"
#include <vector>
UniversalAccount createUniversalAccount(size_t userIdATM, string cardNumber, string pin, string cvv, double sumOnBalance,
                                        size_t limit,string expiryDate,  bool isBlocked){

    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);

 
    UniversalAccount ua(userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,isBlocked,expiryDate);
    expiryDate = ua.expiryDate();
    string sql("INSERT INTO UNIVERSAL_ACCOUNT (account_number,pin,expiry_date, cvv_number, sum_on_balance, user_id, limit, isBlocked)"
               " VALUES('"  + cardNumber + "', '" + pin+ "', '" + expiryDate  + "', '" + cvv + "', "+ to_string(sumOnBalance) + ", "+ to_string(userIdATM) + ", " + to_string(limit) + "," + to_string(isBlocked)+");"
    );


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);

    return ua;

}



CreditAccount createCreditAccount(size_t creditTerm, double creditDept, size_t userIdATM, string cardNumber, string pin, string cvv,
                                  double sumOnBalance, size_t limit, bool isBlocked, string expiryDate,
                                  string creditExpiryDate){

    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);

    CreditAccount ca(creditTerm,creditDept,userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,isBlocked,"");
    expiryDate = ca.expiryDate();
    creditExpiryDate = ca.creditExpiryDate();
    sumOnBalance = ca.sumOnBalance();
    string sql("INSERT INTO CREDIT_ACCOUNT (account_number,pin,expiry_date, cvv_number, sum_on_balance,credit_term,credit_expiry_date,credit_debt, user_id)"
               " VALUES('"  + cardNumber + "', '" + pin+ "', '" + expiryDate  + "', '" + cvv + "', "+ to_string(sumOnBalance) + ", "+ to_string(creditTerm)+", '"+ creditExpiryDate+ "', " + to_string(creditDept)+ ", "+ to_string(userIdATM) + ", " + to_string(limit) + "," + to_string(isBlocked) + ");"
    );


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);

    return ca;
}


DepositAccount createDepositAccount(size_t userIdATM, string cardNumber, string pin, string cvv, double sumOnBalance,
                                    size_t limit,string expiryDate,  bool isBlocked,size_t depositTerm, size_t depositPercentage,
                                    string depositExpiryDate){

    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);

    DepositAccount da(userIdATM,cardNumber,pin,cvv,sumOnBalance,limit,"",false,depositTerm,depositPercentage,"");
    expiryDate = da.expiryDate();
    depositExpiryDate = da.depositExpiryDate();
    sumOnBalance = da.sumOnBalance();
    string sql("INSERT INTO DEPOSIT_ACCOUNT (account_number,pin,expiry_date, cvv_number, sum_on_balance,deposit_term,deposit_expiry_date,deposit_percentage, user_id)"
               " VALUES('"  + cardNumber + "', '" + pin+ "', '" + expiryDate  + "', '" + cvv + "', "+ to_string(sumOnBalance) + ", "+ to_string(depositTerm)+", '"+ depositExpiryDate+ "', " + to_string(depositPercentage)+ ", "+ to_string(userIdATM) +  "," + to_string(isBlocked) + ", " + to_string(limit) + ");"
    );


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);

    return da;
}


UniversalAccount getUniversalAccountByUserId(size_t id){
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM `UNIVERSAL_ACCOUNT` where user_id =" +to_string(id)+";");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	string accountNumber(""), pin(""), expiryDate(""), cvvNumber("");
	int userIdATM(0), sum(0), limit(0), isBlocked(0);
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	int j = 0;
	while ((pos = queryResult.find(delimiter)) != std::string::npos) {
		token = queryResult.substr(0, pos);
		switch (j) {
		case 0:
			if (token == "") {
				return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, false, expiryDate);
			}
			accountNumber = token;
			j++;
			break;
		case 1:
			pin = token;
			j++;
			break;
		case 2:
			expiryDate = token;
			j++;
			break;
		case 3:
			cvvNumber = token;
			j++;
			break;
		case 4:
			sum = stoi(token);
			j++;
			break;
		case 5:
			userIdATM = stoi(token);
			j++;
			break;
		case 6:
			limit = stoi(token);
			j++;
			break;
		case 7:
			isBlocked = stoi(token);
			j++;
			break;
		}

		queryResult.erase(0, pos + delimiter.length());
	}
	
	queryResult = "";
	sqlite3_close(DB);
	bool isBl = isBlocked == 1 ? true : false;
	return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl,expiryDate);
}

UniversalAccount getUniversalAccountByCardAndPin(string card, string pinn){
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM `UNIVERSAL_ACCOUNT` where account_number ='" + card + "' AND pin ='"+pinn+"';");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	string accountNumber(""), pin(""), expiryDate(""), cvvNumber("");
	int userIdATM(0), sum(0), limit(0), isBlocked(0);
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	int j = 0;
	while ((pos = queryResult.find(delimiter)) != std::string::npos) {
		token = queryResult.substr(0, pos);
		switch (j) {
		case 0:
			if (token == "") {
				return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, false, expiryDate);
			}
			accountNumber = token;
			j++;
			break;
		case 1:
			pin = token;
			j++;
			break;
		case 2:
			expiryDate = token;
			j++;
			break;
		case 3:
			cvvNumber = token;
			j++;
			break;
		case 4:
			sum = stoi(token);
			j++;
			break;
		case 5:
			userIdATM = stoi(token);
			j++;
			break;
		case 6:
			limit = stoi(token);
			j++;
			break;
		case 7:
			isBlocked = stoi(token);
			j++;
			break;
		}

		queryResult.erase(0, pos + delimiter.length());
	}
	bool isBl = isBlocked == 1 ? true : false;
	queryResult = "";
	sqlite3_close(DB);
	return UniversalAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit,isBl, expiryDate);
}

CreditAccount getCreditAccountByUserId(size_t id){
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM `CREDIT_ACCOUNT` where user_id =" + to_string(id) + ";");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	string accountNumber(""), pin(""), expiryDate(""), cvvNumber(""),creditExpDate("");
	int userIdATM(0), sum(0), creditTerm(0),creditDebt(0), limit(0), isBlocked(0);
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	int j = 0;
	while ((pos = queryResult.find(delimiter)) != std::string::npos) {
		token = queryResult.substr(0, pos);
		switch (j) {
		case 0:
			if (token == "") {
				return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, false, expiryDate, creditExpDate);
			}
			accountNumber = token;
			j++;
			break;
		case 1:
			pin = token;
			j++;
			break;
		case 2:
			expiryDate = token;
			j++;
			break;
		case 3:
			cvvNumber = token;
			j++;
			break;
		case 4:
			sum = stoi(token);
			j++;
			break;
		case 5:
			creditTerm = stoi(token);
			j++;
			break;
		case 6:
			creditExpDate = token;
			j++;
			break;
		case 7:
			creditDebt = stoi(token);
			j++;
			break;
		case 8:
			userIdATM = stoi(token);
			j++;
			break;
		case 9:
			limit = stoi(token);
			j++;
			break;
		case 10:
			isBlocked = stoi(token);
			j++;
			break;
		}

		queryResult.erase(0, pos + delimiter.length());
	}
	bool isBl = isBlocked == 1 ? true : false;
	queryResult = "";
	sqlite3_close(DB);
	return CreditAccount(creditTerm,creditDebt,userIdATM,accountNumber,pin,cvvNumber,sum,limit,isBl,expiryDate,creditExpDate);
}

CreditAccount getCreditAccountByCardAndPin(string card, string pinn){
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM `CREDIT_ACCOUNT` where account_number ='" + card + "' AND pin ='" + pinn + "';");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	string accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), creditExpDate("");
	int userIdATM(0), sum(0), creditTerm(0), creditDebt(0), limit(0), isBlocked(0);
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	int j = 0;
	while ((pos = queryResult.find(delimiter)) != std::string::npos) {
		token = queryResult.substr(0, pos);
		switch (j) {
		case 0:
			if (token == "") {
				return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, false, expiryDate, creditExpDate);
			}
			accountNumber = token;
			j++;
			break;
		case 1:
			pin = token;
			j++;
			break;
		case 2:
			expiryDate = token;
			j++;
			break;
		case 3:
			cvvNumber = token;
			j++;
			break;
		case 4:
			sum = stoi(token);
			j++;
			break;
		case 5:
			creditTerm = stoi(token);
			j++;
			break;
		case 6:
			creditExpDate = token;
			j++;
			break;
		case 7:
			creditDebt = stoi(token);
			j++;
			break;
		case 8:
			userIdATM = stoi(token);
			j++;
			break;
		case 9:
			limit = stoi(token);
			j++;
			break;
		case 10:
			isBlocked = stoi(token);
			j++;
			break;
		}

		queryResult.erase(0, pos + delimiter.length());
	}
	bool isBl = isBlocked == 1 ? true : false;
	queryResult = "";
	sqlite3_close(DB);
	return CreditAccount(creditTerm, creditDebt, userIdATM, accountNumber, pin, cvvNumber, sum, limit, isBl, expiryDate, creditExpDate);
}

DepositAccount getDepositAccountByUserId(size_t id){
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM `DEPOSIT_ACCOUNT` where user_id =" + to_string(id) + ";");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	string accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), depositExpDate("");
	int userIdATM(0), sum(0), depositTerm(0),limit(0),isBlocked(0);
	double depositPerc(0.0);
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	int j = 0;
	while ((pos = queryResult.find(delimiter)) != std::string::npos) {
		token = queryResult.substr(0, pos);
		switch (j) {
		case 0:
			if (token == "") {
				return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, false, depositTerm, depositPerc, depositExpDate);
			}
			accountNumber = token;
			j++;
			break;
		case 1:
			pin = token;
			j++;
			break;
		case 2:
			expiryDate = token;
			j++;
			break;
		case 3:
			cvvNumber = token;
			j++;
			break;
		case 4:
			sum = stoi(token);
			j++;
			break;
		case 5:
			depositTerm = stoi(token);
			j++;
			break;
		case 6:
			depositExpDate = token;
			j++;
			break;
		case 7:
			depositPerc = stod(token);
			j++;
			break;
		case 8:
			userIdATM = stoi(token);
			j++;
			break;
		case 9:
			limit = stoi(token);
			j++;
			break;
		case 10:
			isBlocked = stoi(token);
			j++;
			break;
		}

		queryResult.erase(0, pos + delimiter.length());
	}
	bool isBl = isBlocked == 1 ? true : false;
	queryResult = "";
	sqlite3_close(DB);
	return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);
}

DepositAccount getDepositAccountByCardAndPin(string card, string pinn){
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM `DEPOSIT_ACCOUNT` where account_number ='" + card + "' AND pin ='" + pinn + "';");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	string accountNumber(""), pin(""), expiryDate(""), cvvNumber(""), depositExpDate("");
	int userIdATM(0), sum(0), depositTerm(0),limit(0), isBlocked(0);
	double depositPerc(0.0);
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	int j = 0;
	while ((pos = queryResult.find(delimiter)) != std::string::npos) {
		token = queryResult.substr(0, pos);
		switch (j) {
		case 0:
			if (token == "") {
				return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, false, depositTerm, depositPerc, depositExpDate);
			}
			accountNumber = token;
			j++;
			break;
		case 1:
			pin = token;
			j++;
			break;
		case 2:
			expiryDate = token;
			j++;
			break;
		case 3:
			cvvNumber = token;
			j++;
			break;
		case 4:
			sum = stoi(token);
			j++;
			break;
		case 5:
			depositTerm = stoi(token);
			j++;
			break;
		case 6:
			depositExpDate = token;
			j++;
			break;
		case 7:
			depositPerc = stod(token);
			j++;
			break;
		case 8:
			userIdATM = stoi(token);
			j++;
			break;
		case 9:
			isBlocked = stoi(token);
			j++;
			break;
		case 10:
			limit = stoi(token);
			j++;
			break;
		}

		queryResult.erase(0, pos + delimiter.length());
	}
	bool isBl = isBlocked == 1 ? true : false;
	
	queryResult = "";
	sqlite3_close(DB);
	return DepositAccount(userIdATM, accountNumber, pin, cvvNumber, sum, limit, expiryDate, isBl, depositTerm, depositPerc, depositExpDate);
}

void withdrawMoneyFromCreditAccount(size_t amount, CreditAccount& ca){
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);

    string card = ca.cardNumber();
    double sum = ca.sumOnBalance() - amount;
    ca.withdrawMoney(amount);
    string sql("UPDATE `CREDIT_ACCOUNT` set `sum_on_balance` ="+ to_string(sum) + " where `account_number` ='" + card + "';"
    );


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }


    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
}



void withdrawMoneyFromUniversalAccount(size_t amount, UniversalAccount& ua){
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);

    string card = ua.cardNumber();
    double sum = ua.sumOnBalance() - amount;
    ua.withdrawMoney(amount);
    string sql("UPDATE `UNIVERSAL_ACCOUNT` set `sum_on_balance` ="+ to_string(sum) + " where `account_number` ='" + card + "';"
    );


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
}


void putMoneyOnCreditAccount(size_t amount, CreditAccount& ca){
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);

    string card = ca.cardNumber();
    double sum = ca.creditDept() - amount;
    ca.putMoney(amount);
    string sql("UPDATE `CREDIT_ACCOUNT` set `credit_debt` ="+ to_string(sum) + " where `account_number` ='" + card + "';"
    );


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
}


void putMoneyOnUniversalAccount(size_t amount, UniversalAccount& ua){
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);


    string card = ua.cardNumber();
    double sum = ua.sumOnBalance() + amount;
    ua.putMoney(amount);
    string sql("UPDATE `UNIVERSAL_ACCOUNT` set `sum_on_balance` ="+ to_string(sum) + " where `account_number` ='" + card + "';"
    );


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
}

void putMoneyOnDepositAccount(size_t amount, DepositAccount& da){
    sqlite3* DB;
    char* messaggeError;
    int exit = sqlite3_open("ATM.db", &DB);

    string card = da.cardNumber();
    double sum = da.sumOnBalance() + amount;
    da.putMoney(amount);
    string sql("UPDATE `DEPOSIT_ACCOUNT` set `sum_on_balance` ="+ to_string(sum) + " where `account_number` ='" + card + "';"
    );


    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        printf(messaggeError);
    }

    sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    sqlite3_close(DB);
}

void putMoneyOnAccountByCard(size_t amount, string card) {
	size_t id = selectUserByCard(card).id();
	if (id != NULL) {
		UniversalAccount ua = getUniversalAccountByUserId(id);
		if (ua.cardNumber() != "") {
			putMoneyOnUniversalAccount(amount, ua);
		}
		else {
			CreditAccount ca = getCreditAccountByUserId(id);
			if (ca.cardNumber() != "") {
				putMoneyOnCreditAccount(amount, ca);
			}
			else {
				DepositAccount da = getDepositAccountByUserId(id);
				putMoneyOnDepositAccount(amount, da);
			}
		}
	}
}

void blockCard(string card) {
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("UPDATE DEPOSIT_ACCOUNT set isBlocked=1 where account_number ='" + card + "' ;"
	);
	
	string sql1("UPDATE CREDIT_ACCOUNT set isBlocked=1   where account_number ='" + card + "';"
	);

	string sql2("UPDATE UNIVERSAL_ACCOUNT set isBlocked=1  where account_number ='" + card + "' ;"
	);


	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error update" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}
	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

	sqlite3_exec(DB, sql1.c_str(), callback, NULL, NULL);

	sqlite3_exec(DB, sql2.c_str(), callback, NULL, NULL);


	
	sqlite3_close(DB);
}

void updateLimit(string card, int newLimit) {
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);
	queryResult = "";
	string sql("SELECT * FROM DEPOSIT_ACCOUNT where account_number = '" + card + "';");

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		string sqlUpd1("UPDATE `DEPOSIT_ACCOUNT` set `limit` = " + to_string(newLimit) + " where `account_number` ='" + card + "' ;");
		sqlite3_exec(DB, sqlUpd1.c_str(), callback, NULL, NULL);
		queryResult = "";
	}

	string sql1("SELECT * FROM CREDIT_ACCOUNT where account_number = '" + card + "';");
	sqlite3_exec(DB, sql1.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		string sqlUpd2("UPDATE `CREDIT_ACCOUNT` set `limit` = " + to_string(newLimit) + " where `account_number` ='" + card + "' ;");
		sqlite3_exec(DB, sqlUpd2.c_str(), callback, NULL, NULL);
		queryResult = "";
	}

	string sql2("SELECT * FROM UNIVERSAL_ACCOUNT where account_number = '" + card + "';");
	sqlite3_exec(DB, sql2.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		string sqlUpd3("UPDATE `UNIVERSAL_ACCOUNT` set `limit` = " + to_string(newLimit) + " where `account_number` ='" + card + "' ;");
		sqlite3_exec(DB, sqlUpd3.c_str(), callback, NULL, NULL);
		queryResult = "";
	}

	queryResult = "";

	sqlite3_close(DB);
}

bool cardExists(string card) {
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM DEPOSIT_ACCOUNT where DEPOSIT_ACCOUNT.account_number = '" + card + "';");
	string sql1("SELECT * FROM CREDIT_ACCOUNT where CREDIT_ACCOUNT.account_number = '" + card + "';");
	string sql2("SELECT * FROM UNIVERSAL_ACCOUNT where UNIVERSAL_ACCOUNT.account_number = '" + card + "';");
	bool exists = false;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		exists = true;
	
	}
	sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messaggeError);
	sqlite3_exec(DB, sql1.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		exists = true;
	}
	sqlite3_exec(DB, sql2.c_str(), NULL, 0, &messaggeError);
	sqlite3_exec(DB, sql2.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		exists = true;
	}
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}
	queryResult = "";
	sqlite3_close(DB);
	return exists;
	
}

bool cardBlocked(string card) {
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM DEPOSIT_ACCOUNT where account_number = '" + card + "' AND isBlocked = 1;");
	string sql1("SELECT * FROM CREDIT_ACCOUNT where account_number = '" + card + "'AND isBlocked = 1;");
	string sql2("SELECT * FROM UNIVERSAL_ACCOUNT where account_number = '" + card + "'AND isBlocked = 1;");
	bool blocked = false;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		blocked = true;
	
	}
	sqlite3_exec(DB, sql1.c_str(), NULL, 0, &messaggeError);
	sqlite3_exec(DB, sql1.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		blocked = true;
	}
	sqlite3_exec(DB, sql2.c_str(), NULL, 0, &messaggeError);
	sqlite3_exec(DB, sql2.c_str(), callback, NULL, NULL);
	if (queryResult != "") {
		blocked = true;
	}
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}
	queryResult = "";
	sqlite3_close(DB);
	return blocked;

}


#endif //STARBANKATM_MOOP_KMA_ACCOUNTSERVICE_H