#include <iostream>
#include <time.h>
#include "models/Transaction.h"
#include "models/accounts/CreditAccount.h"
#include "models/accounts/DepositAccount.h"
#include "models/accounts/UniversalAccount.h"

#include "DBService/UserService.h"
#include "DBService/TransactionService.h"
#include "DBService/AccountService.h"
#include "ATM.h"
#include <cassert>


void convetSecToTime(int time) {
    int day = time / 24 / 3600;
    int hours = time / 3600 - day * 24;
    int min = time / 60 - day * 24 * 60 - hours * 60;
    int sec = time - day * 24 * 3600 - hours * 3600 - min * 60;
    cout << day << " days " << hours << " hours " << min << " min " << sec << " sec " << endl;
}

ATM::ATM() :isWorking(true), _dispenser(*this) {
}

void ATM::work() {
    enjectingCard();
    while (isWorking) {
        startSession();
    }
    terminateSession();
}

void ATM::startSession() {


    cout << "WELCOME \n";
    user = selectUserById(userId);
    cout << user.firstName() << '\t' << user.lastName() << endl;


    switch (accountType) {
    case 'd': {
        bool isON = true;
        while (isON) {
            cout << "CHOOSE OPERATION:" << endl;
            cout << "1 - PUT MONEY" << endl;
            cout << "2 - CHECK BALANCE" << endl;
            cout << "3 - CHECK LIMIT" << endl;
            cout << "4 - CHANGE LIMIT" << endl;
            cout << "5 - SHOW DEPOSIT TERM" << endl;
            cout << "6 - SHOW DEPOSIT PERCENTAGE" << endl;
            cout << "7 - SHOW DEPOSIT EXPIRY DATE" << endl;
			cout << "8 - SHOW ALL TRANSACTIONS" << endl;
            cout << "0 - EXIT" << endl;
            int choosen;
            cin >> choosen;
            switch (choosen) {
            case 1:
			{
				bool notFinished = true;
				int sum(0);
				while (notFinished) {
					cout << "INSERT CASH: " << endl;
					int sumPut;
					cin >> sumPut;
					getDispenser().incashMoney(sumPut);
					if (!getDispenser().wrongBanknote()) {
						sum += sumPut;
					}
					cout << " WHEN YOU ARE READY TO DEPOSIT, ENTER OK" << endl;
					cout << "ELSE ENTER ANY OTHER SYMBOL" << endl;
					string answ = "";
					cin >> answ;
					if (answ == "OK") {
						putMoneyOnDepositAccount(sum, depositAccount);
						notFinished = false;
					}
				}
				break;
			}
            case 2:
                cout << "YOUR BALANCE: " << depositAccount.sumOnBalance() << endl;
                break;
            case 3:
                cout << "YOUR LIMIT: " << depositAccount.limit() << endl;
                break;
            case 4:
                cout << "ENTER NEW LIMIT: ";
                int limit;
                cin >> limit;
                depositAccount.limit() = limit;
                cout << "YOUR NEW LIMIT: " << depositAccount.limit() << endl;
                break;
            case 5:
                cout << "YOUR DEPOSIT TERM: " << endl;
                convetSecToTime(depositAccount.depositTerm());
                break;
            case 6:
                cout << "YOUR DEPOSIT PERCENTAGE: " << depositAccount.depositPercentage() << " % " << endl;
                break;
            case 7:
                cout << "YOUR DEPOSIT EXPIRY DATE: " << depositAccount.depositExpiryDate() << endl;
                break;
			case 8:
				showAllTransactionsByCard(depositAccount.cardNumber());
				break;
            case 0:
				isON = false;
				isWorking = false;
                break;
            default:
                cout << "INVALID ENTER" << endl;
                break;
            }
            cout << endl;
        }
        break;
    }
    case 'u': {
        bool isON = true;
        while (isON) {
            cout << "CHOOSE OPERATION:" << endl;
            cout << "1 - PUT MONEY" << endl;
            cout << "2 - WITHDRAW MONEY" << endl;
            cout << "3 - CHECK BALANCE" << endl;
            cout << "4 - CHECK LIMIT" << endl;
            cout << "5 - CHANGE LIMIT" << endl;
            cout << "6 - PUT MONEY TO ANOTHER ACCOUNT" << endl;
            cout << "7 - PUT MONEY TO MY ACCOUNT" << endl;
			cout << "8 - SHOW ALL TRANSACTIONS" << endl;
			cout << "0 - EXIT" << endl;
            int choosen;
            cin >> choosen;
            switch (choosen) {
			case 1: {
				bool notFinished = true;
				int sum(0);
				while (notFinished) {
					cout << "INSERT CASH: " << endl;
					int sumPut;
					cin >> sumPut;
					getDispenser().incashMoney(sumPut);
					if (!getDispenser().wrongBanknote()) {
						sum += sumPut;
					}
					cout << " WHEN YOU ARE READY TO DEPOSIT, ENTER OK" << endl;
					cout << "ELSE ENTER ANY OTHER SYMBOL" << endl;
					string answ = "";
					cin >> answ;
					if (answ == "OK") {
						putMoneyOnUniversalAccount(sum, universalAccount);
						notFinished = false;
					}
				}
				break;
			}
            case 2:
                if (getDispenser().isBlocked()) {
                    cout << "ATM doesn't have enough money" << endl;
                }
                else {
                    cout << "ENTER AMOUNT OF MONEY TO WITHDRAW: " << endl;
                    int sumOut;
                    cin >> sumOut;
                    if (sumOut <= universalAccount.sumOnBalance()) {
                        if (sumOut <= universalAccount.limit()) {
                            getDispenser().getNotesOut(sumOut);
                            if (getDispenser().amountIsOk()) {
                                withdrawMoneyFromUniversalAccount(sumOut, universalAccount);
                            }
                        }
                        else {
                            cout << "THE AMOUNT IS MORE THAN YOUR LIMIT" << endl;
                            cout << "ENTER ANOTHER AMOUNT OR CHANGE YOUR LIMIT" << endl;
                        }
                    }
                    else {
                        cout << "YOU DO NOT HAVE ENOUGHT MONEY" << endl;
                    }
                }

                break;
            case 3:
                cout << "YOUR BALANCE: " << universalAccount.sumOnBalance() << endl;
                break;
            case 4:
                cout << "YOUR LIMIT: " << universalAccount.limit() << " UAH " << endl;
                break;
            case 5:
                cout << "ENTER NEW LIMIT: ";
                int limit;
                cin >> limit;
                universalAccount.limit() = limit;
				updateLimit(universalAccount.cardNumber(), limit);
                cout << "YOUR NEW LIMIT: " << universalAccount.limit() << " UAH " << endl;
                break;
            case 6: {
                cout << "ENTER SUM TO PUT: " << endl;
                int sumPut2;
                cin >> sumPut2;
                if (sumPut2 <= universalAccount.sumOnBalance()) {
                    if (sumPut2 > universalAccount.limit()) {
                        cout << "THE AMOUNT IS MORE THAN YOUR LIMIT" << endl;
                        cout << "ENTER ANOTHER AMOUNT OR CHANGE YOUR LIMIT" << endl;
                        break;
                    }
                    cout << "ENTER CARD NUMBER TO PUT: " << endl;
                    string cardPut;
                    cin >> cardPut;

                    if (cardExists(cardPut)) {
                        makeTransactionFromUniversalToAnother(universalAccount, cardPut, sumPut2,true);
                    }
                    else {
                        cout << "DO YOU WANT TO PUT MONEY TO THE CARD OF ANOTHER BANK (Y/N)?" << endl;
                        string answ;
                        cin >> cardPut;
                        if (answ == "Y") {
                            makeTransactionFromUniversalToAnother(universalAccount, cardPut, sumPut2,false);
                        }
                        else {
                            //exit to menu
                        }
                    }
                }
                else {
                    cout << "YOU DO NOT HAVE ENOUGHT MONEY" << endl;
                }

                break; }
            case 7:
                cout << "ENTER SUM TO PUT: " << endl;
                int sumPut3;
                cin >> sumPut3;
                if (sumPut3 <= universalAccount.sumOnBalance()) {
                    if (sumPut3 > universalAccount.limit()) {
                        cout << "THE AMOUNT IS MORE THAN YOUR LIMIT" << endl;
                        cout << "ENTER ANOTHER AMOUNT OR CHANGE YOUR LIMIT" << endl;
                        break;
                    }
                    cout << "WHICH ACCOUNT DO YOU WANT TO PUT MONEY TO? " << endl;
                    cout << "1 - DEPOSIT ACCOUNT" << endl;
                    cout << "2 - CREDIT ACCOUNT" << endl;
                    char acctype;
                    cin >> acctype;
                    if (acctype == '1') makeTransactionFromUniversalToDeposit(universalAccount, depositAccount, sumPut3);
                    else if (acctype == '2')  makeTransactionFromUniversalToCredit(universalAccount, creditAccount, sumPut3);
                }
                else {
                    cout << "YOU DO NOT HAVE ENOUGHT MONEY" << endl;
                }
                break;
			case 8:
				showAllTransactionsByCard(depositAccount.cardNumber());
				break;
            case 0:
                isON = false;
                isWorking = false;
                break;
            default:
                cout << "INVALID ENTER" << endl;
                break;
            }
            cout << endl;
        }
        break;
    }
    case 'c': {
        bool isON = true;
        while (isON) {
            cout << "CHOOSE OPERATION:" << endl;
            cout << "1 - PUT MONEY" << endl;
            cout << "2 - WITHDRAW MONEY" << endl;
            cout << "3 - CHECK BALANCE" << endl;
            cout << "4 - CHECK LIMIT" << endl;
            cout << "5 - CHANGE LIMIT" << endl;
            cout << "6 - PUT MONEY TO ANOTHER ACCOUNT" << endl;
            cout << "7 - PUT MONEY TO MY ACCOUNT" << endl;
			cout << "8 - SHOW ALL TRANSACTIONS" << endl;
            cout << "0 - EXIT" << endl;
            int choosen;
            cin >> choosen;
            switch (choosen) {
            case 1:
			{
				bool notFinished = true;
				int sum(0);
				while (notFinished) {
					cout << "INSERT CASH: " << endl;
					int sumPut;
					cin >> sumPut;
					getDispenser().incashMoney(sumPut);
					if (!getDispenser().wrongBanknote()) {
						sum += sumPut;
					}
					cout << " WHEN YOU ARE READY TO DEPOSIT, ENTER OK" << endl;
					cout << "ELSE ENTER ANY OTHER SYMBOL" << endl;
					string answ = "";
					cin >> answ;
					if (answ == "OK") {
						putMoneyOnCreditAccount(sum, creditAccount);
						notFinished = false;
					}
				}
				break;
			}
            case 2:
                if (getDispenser().isBlocked()) {
                    cout << "ATM doesn't have enough money" << endl;
                }
                else {
                    cout << "ENTER AMOUNT OF MONEY TO WITHDRAW: " << endl;
                    int sumOut;
                    cin >> sumOut;

                    if (sumOut <= creditAccount.sumOnBalance()) {
                        if (sumOut <= creditAccount.limit()) {
                            getDispenser().getNotesOut(sumOut);
                            if (getDispenser().amountIsOk()) {
                                withdrawMoneyFromCreditAccount(sumOut, creditAccount);
                            }
                        }
                        else {
                            cout << "THE AMOUNT IS MORE THAN YOUR LIMIT" << endl;
                            cout << "ENTER ANOTHER AMOUNT OR CHANGE YOUR LIMIT" << endl;
                        }
                    }
                    else {
                        cout << "YOU DO NOT HAVE ENOUGHT MONEY" << endl;
                    }
                }

                break;
            case 3:
                cout << "YOUR BALANCE: " << creditAccount.sumOnBalance() << " UAH " << endl;
                break;
            case 4:
                cout << "YOUR LIMIT: " << creditAccount.limit() << " UAH " << endl;
                break;
            case 5:
                cout << "ENTER NEW LIMIT: ";
                int limit;
                cin >> limit;
                creditAccount.limit() = limit;
				updateLimit(creditAccount.cardNumber(), limit);
                cout << "YOUR NEW LIMIT: " << creditAccount.limit() << " UAH " << endl;
                break;
            case 6: {

                cout << "ENTER SUM TO PUT: " << endl;
                int sumPut2;
                cin >> sumPut2;
                if (sumPut2 <= creditAccount.sumOnBalance()) {
                    if (sumPut2 > creditAccount.limit()) {
                        cout << "THE AMOUNT IS MORE THAN YOUR LIMIT" << endl;
                        cout << "ENTER ANOTHER AMOUNT OR CHANGE YOUR LIMIT" << endl;
                        break;
                    }
                    cout << "ENTER CARD NUMBER TO PUT: " << endl;
                    string cardPut;
                    cin >> cardPut;

                    if (cardExists(cardPut)) {
                        makeTransactionFromCreditToAnother(creditAccount, cardPut, sumPut2,true);
                    }
                    else {
                        cout << "DO YOU WANT TO PUT MONEY TO THE CARD OF ANOTHER BANK (Y/N)?" << endl;
                        string answ;
                        cin >> cardPut;
                        if (answ == "Y") {
                            makeTransactionFromCreditToAnother(creditAccount, cardPut, sumPut2,false);
                        }
                        else {
                            //exit to menu
                        }
                    }
                }
                else {
                    cout << "YOU DO NOT HAVE ENOUGHT MONEY" << endl;
                }

                break;
            }
            case 7:
                cout << "ENTER SUM TO PUT: " << endl;
                int sumPut3;
                cin >> sumPut3;
                if (sumPut3 <= creditAccount.sumOnBalance()) {
                    if (sumPut3 > creditAccount.limit()) {
                        cout << "THE AMOUNT IS MORE THAN YOUR LIMIT" << endl;
                        cout << "ENTER ANOTHER AMOUNT OR CHANGE YOUR LIMIT" << endl;
                        break;
                    }
                    cout << "WHICH ACCOUNT DO YOU WANT TO PUT MONEY TO? " << endl;
                    cout << "1 - DEPOSIT ACCOUNT" << endl;
                    cout << "2 - UNIVERSAL ACCOUNT" << endl;
                    char acctype;
                    cin >> acctype;
                    if (acctype == '1') makeTransactionFromCreditToDeposit(creditAccount, depositAccount, sumPut3);
                    else if (acctype == '2')  makeTransactionFromCreditToUniversal(creditAccount, universalAccount, sumPut3);

                }
                else {
                    cout << "YOU DO NOT HAVE ENOUGHT MONEY" << endl;
                }
                break;
			case 8:
				showAllTransactionsByCard(depositAccount.cardNumber());
				break;
            case 0:
                isWorking = false;
                isON = false;
                break;
            default:
                cout << "INVALID ENTER" << endl;
                break;
            }
            cout << endl;
        }
        break;
    }
    default:
        break;
    }

    isWorking = false;
}

void ATM::terminateSession() {
    rejectionCard();
    cout << "THANK YOU FOR USING OUR ATM" << endl;
    system(0);
}

void ATM::rejectionCard() {
    cout << "REJECTING CARD...." << endl;
}

void ATM::blockingCard(string card) {
    cout << "BLOCKING CARD..." << endl;
    cout << "CALL YOUR BANK ASSISTANT TO ACTIVATE YOUR CARD" << endl;
    blockCard(card);
    isWorking = false;
}

void ATM::enjectingCard() {
    string card, pin;
    bool notEjected = true;
    bool validCard = false;

    while (notEjected) {

        for (int j = 0; j < 3; j++) {
            cout << "ENTER YOUR CARD NUMBER: ";
            getline(cin, card);
            if (cardExists(card)) {
                if (!cardBlocked(card)) {
                    validCard = true;
                    break;
                }
                else {
                    cout << "YOUR CARD IS BLOCKED!!! ENTER ANOTHER CARD!!!" << endl;
                }
            }
            if (j == 2) {
                cout << "TERMINATING SESSION" << endl;
                isWorking = false;
                notEjected = false;
            }
            else {
                cout << "THIS IS NOT A CARD!!!" << endl;
                rejectionCard();
            }
        }
        if (validCard) {
            for (int i = 0; i < 3; i++) {
                cout << "ENTER YOUR PIN: ";
                getline(cin, pin);

                if (!getDepositAccountByCardAndPin(card, pin).cardNumber().empty()) {
                    accountType = 'd';
                    depositAccount = getDepositAccountByCardAndPin(card, pin);
                    universalAccount = getUniversalAccountByUserId(depositAccount.userId());
                    creditAccount = getCreditAccountByUserId(depositAccount.userId());
                    userId = depositAccount.userId();
                    notEjected = false;
                    break;
                }
                else if (!getUniversalAccountByCardAndPin(card, pin).cardNumber().empty()) {
                    accountType = 'u';
                    universalAccount = getUniversalAccountByCardAndPin(card, pin);
                    depositAccount = getDepositAccountByUserId(universalAccount.userId());
                    creditAccount = getCreditAccountByUserId(universalAccount.userId());
                    userId = universalAccount.userId();
                    notEjected = false;
                    break;
                }
                else if (!getCreditAccountByCardAndPin(card, pin).cardNumber().empty()) {
                    accountType = 'c';
                    creditAccount = getCreditAccountByCardAndPin(card, pin);
                    universalAccount = getUniversalAccountByUserId(creditAccount.userId());
                    depositAccount = getDepositAccountByUserId(creditAccount.userId());
                    userId = creditAccount.userId();
                    notEjected = false;
                    break;
                }
                else {
                    cout << "WRONG CARD OR PIN!!!" << endl;
                }
            }
        }
        if (notEjected) {
            blockingCard(card);
            break;
        }
    }

}

void ATM::showAllTransactionsByCard(string card) {
	list<Transaction> t = getAllTransactionsByCard(card);
	for (list<Transaction>::iterator it = t.begin(); it != t.end(); ++it) {
		cout << *it;
	}
}

void test() {

	UniversalAccount universalAccount = getUniversalAccountByCardAndPin("8887", "000");
	DepositAccount depositAcount = getDepositAccountByCardAndPin("2355", "111");
	CreditAccount creditAcount = getCreditAccountByCardAndPin("7777", "111");

	//testing limit
	int newLimit = 1000;
	universalAccount.limit() = newLimit;
	updateLimit(universalAccount.cardNumber(), newLimit);
	assert(newLimit == universalAccount.limit());

	//testing blocking
	DepositAccount depositAccountToBlock = getDepositAccountByCardAndPin("5667", "677");
	blockCard(depositAccountToBlock.cardNumber());
	depositAccountToBlock = getDepositAccountByCardAndPin("5667", "677");
	assert(true == depositAccountToBlock.isBlocked());

	//testing putting money on Universal Account
	double oldAmount = universalAccount.sumOnBalance();
	double amount = 100;
	putMoneyOnUniversalAccount(amount, universalAccount);
	double newAmount = oldAmount + amount;
	assert(newAmount == universalAccount.sumOnBalance());

	//testing putting money on Deposit Account
	oldAmount = depositAcount.sumOnBalance();
	amount = 100;
	putMoneyOnDepositAccount(amount, depositAcount);
	newAmount = oldAmount + amount;
	assert(newAmount == depositAcount.sumOnBalance());

	//testing withdrawing money from Universal Account
	oldAmount = universalAccount.sumOnBalance();
	amount = 100;
	withdrawMoneyFromUniversalAccount(amount, universalAccount);
	newAmount = oldAmount - amount;
	assert(newAmount == universalAccount.sumOnBalance());

	//testing withdrawing money from Credit Account
	oldAmount = creditAcount.sumOnBalance();
	amount = 100;
	withdrawMoneyFromCreditAccount(amount, creditAcount);
	newAmount = oldAmount - amount;
	assert(newAmount == creditAcount.sumOnBalance());

	//testing Transaction from Universal To Deposit
	amount = 100;
	double oldAmountOnDeposit = depositAcount.sumOnBalance();
	double oldAmountOnUniversal = universalAccount.sumOnBalance();
	makeTransactionFromUniversalToDeposit(universalAccount, depositAcount, amount);
	double newAmountOnUniversal5 = oldAmountOnUniversal - amount;
	assert(newAmountOnUniversal5 == universalAccount.sumOnBalance());
	double newAmountOnDeposit5 = oldAmountOnDeposit + amount;
	assert(newAmountOnDeposit5 == depositAcount.sumOnBalance());

	//testing Transaction from Universal To Credit
	amount = 100;
	double oldDeptOnCredit6 = creditAcount.creditDept();
	double oldAmountOnUniversal6 = universalAccount.sumOnBalance();
	makeTransactionFromUniversalToCredit(universalAccount, creditAcount, amount);
	double newAmountOnUniversal6 = oldAmountOnUniversal6 - amount;
	assert(newAmountOnUniversal6 == universalAccount.sumOnBalance());
	double newDeptOnCredit6 = oldDeptOnCredit6 - amount;
	assert(newDeptOnCredit6 == creditAcount.creditDept());

	//testinf Transaction from Universal To Another account
	amount = 300;
	double oldAmountOnUniversal7 = universalAccount.sumOnBalance();
	double newAmountOnUniversal7 = oldAmountOnUniversal7 - amount;
	makeTransactionFromUniversalToAnother(universalAccount, "9999", amount, false);
	assert(newAmountOnUniversal7 == universalAccount.sumOnBalance());

	//testing Transaction from Credit To Universal
	amount = 100;
	double oldAmountOnCredit6 = creditAcount.sumOnBalance();
	oldAmountOnUniversal6 = universalAccount.sumOnBalance();
	makeTransactionFromCreditToUniversal(creditAcount, universalAccount, amount);
	newAmountOnUniversal6 = oldAmountOnUniversal6 + amount;
	assert(newAmountOnUniversal6 == universalAccount.sumOnBalance());
	double newAmountOnCredit6 = oldAmountOnCredit6 - amount;
	assert(newAmountOnCredit6 == creditAcount.sumOnBalance());

	//testing Transaction from Credit To Deposit
	amount = 100;
	oldAmountOnCredit6 = creditAcount.sumOnBalance();
	oldAmountOnDeposit = depositAcount.sumOnBalance();
	makeTransactionFromCreditToDeposit(creditAcount, depositAcount, amount);
	double newAmountOnDeposit = oldAmountOnDeposit + amount;
	assert(newAmountOnDeposit == depositAcount.sumOnBalance());
	newAmountOnCredit6 = oldAmountOnCredit6 - amount;
	assert(newAmountOnCredit6 == creditAcount.sumOnBalance());

}
