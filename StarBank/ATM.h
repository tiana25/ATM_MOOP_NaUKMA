#pragma once


#include "models/accounts/DepositAccount.h"
#include "models/accounts/UniversalAccount.h"
#include "models/accounts/CreditAccount.h"
#include "CashDispencer.h"


#ifndef STARBANKATM_MOOP_KMA_ATM_H
#define STARBANKATM_MOOP_KMA_ATM_H


class ATM {
private:
	CashDispencer  _dispenser;
	bool isWorking;
	DepositAccount depositAccount;
	UniversalAccount universalAccount;
	CreditAccount creditAccount;
	int userId;
	User user;
	char accountType = ' ';
public:
	ATM();
	~ATM() {}
	CashDispencer& getDispenser() { return _dispenser; }
	void startSession();
	void terminateSession();
	void work();
	void enjectingCard();
	void rejectionCard();
	void blockingCard(string card);
	void showAllTransactionsByCard(string card);
};
void test();
#endif //STARBANKATM_MOOP_KMA_ATM_H