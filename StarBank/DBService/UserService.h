
#ifndef STARBANKATM_MOOP_KMA_USERSERVICE_H
#define STARBANKATM_MOOP_KMA_USERSERVICE_H
#include <cstdio>
#include "../sqlite3.h"
#include <vector>
#include "../models/User.h"

string queryResult;
 static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		queryResult += argv[i];
		queryResult += ";";

	}
	return 0;
}

void createUser(size_t iduser, string firstname, string lastname, string middlename) {

	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("INSERT INTO USER (id_user,first_name,last_name,middle_name)"
		" VALUES(" + to_string(iduser) + ", '" + firstname + "', '" + lastname + "', '" + middlename + "');"
	);

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error Insert" << std::endl;
		sqlite3_free(messaggeError);

	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);

}


User selectUserById(size_t idd) {

	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);

	string sql("SELECT * FROM USER where id_user ='" + to_string(idd) + "';");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	string firstName(""), lastName(""), middleName("");
	int id(0);
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	int j = 0;
	while ((pos = queryResult.find(delimiter)) != std::string::npos) {
		token = queryResult.substr(0, pos);
		switch (j) {
		case 0:
			if (token == "") {
				return User(id, firstName, lastName, middleName);
			}
			id = stoi(token);
			j++;
			break;
		case 1:
			firstName = token;
		
			j++;
			break;
		case 2:
			lastName = token;
		
			j++;
			break;
		case 3:
			middleName = token;
		
			j++;
			break;
		}

		queryResult.erase(0, pos + delimiter.length());
	}
	
	queryResult = "";

	sqlite3_close(DB);
	return User (id, firstName, lastName, middleName);
}

User selectUserByCard(string card) {

	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);
	string sql("SELECT * FROM USER WHERE id_user IN (SELECT user_id FROM CREDIT_ACCOUNT WHERE account_number='" + card + "') OR  id_user IN (SELECT user_id FROM DEPOSIT_ACCOUNT WHERE account_number='" + card + "') OR  id_user IN (SELECT user_id FROM UNIVERSAL_ACCOUNT WHERE account_number='" + card + "');");

	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error SELECT" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);
	string firstName(""), lastName(""), middleName("");
	int id(0);
	std::string delimiter = ";";
	size_t pos = 0;
	std::string token;
	int j = 0;
	while ((pos = queryResult.find(delimiter)) != std::string::npos) {
		token = queryResult.substr(0, pos);
		switch (j) {
		case 0:
			if (token == "") {
				return User(id, firstName, lastName, middleName);
			}
			id = stoi(token);
			j++;
			break;
		case 1:
			firstName = token;
	
			j++;
			break;
		case 2:
			lastName = token;
		
			j++;
			break;
		case 3:
			middleName = token;
	
			j++;
			break;
		}

		queryResult.erase(0, pos + delimiter.length());
	}

	queryResult = "";
	
	sqlite3_close(DB);
	return User (id, firstName, lastName, middleName);

}



void deleteUsers(size_t iduser) {
	sqlite3* DB;
	char* messaggeError;
	int exit = sqlite3_open("ATM.db", &DB);
	string sql("DELETE FROM USER WHERE id_user = " + to_string(iduser) + "; ");
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error DELETE" << std::endl;
		sqlite3_free(messaggeError);
		printf(messaggeError);
	}

	sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

	sqlite3_close(DB);

}
#endif //STARBANKATM_MOOP_KMA_USERSERVICE_H