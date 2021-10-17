#include "SessionManager.h"
#include "TransactionService.h"
#include <QMessageBox>


CreditAccount SessionManager::_ca;
UniversalAccount SessionManager::_ua;
DepositAccount SessionManager::_da;

QString SessionManager::_card("");
QString SessionManager::_pin("");
bool SessionManager::_isDeposit = false;;
bool SessionManager::_isCredit = false;
bool SessionManager::_isUniversal = false;
bool SessionManager::_cardPinOk = false;

SessionManager::SessionManager(SessionManager &sm) :
        _totalCashAmount(sm.getTotalCash()), _notesMap(sm.getMap()), _success(sm.isSuccess()),
        _cardOk(sm.cardNumIsOk()), _numTry(sm.getTry()) {
    initialiseNotes();
}

//cash disp
void SessionManager::incashMoney(int n) {
    if (n != 50 && n != 100 && n != 200 && n != 500) {
        _success = false;
        QMessageBox::warning(NULL, QObject::tr("Error"),
                             QObject::tr("Wrong banknote! Try again!"), QMessageBox::Cancel);
    } else {
        _notesMap[n]++;
        setTotalCashAmount();
        _success = true;
    }

}


void SessionManager::initialiseNotes() {
    _notesMap[50] = get50();
    _notesMap[100] = get100();
    _notesMap[200] = get200();
    _notesMap[500] = get500();
    setTotalCashAmount();
}

void SessionManager::setTotalCashAmount() {
    int total = 0;
    total += _notesMap[50] * 50;
    total += _notesMap[100] * 100;
    total += _notesMap[200] * 200;
    total += _notesMap[500] * 500;
    _totalCashAmount = total;
}

void SessionManager::calculateNotesOut(int m) {
    _smallAmount = false;
    _notDivisible = false;
    _notEnoughMoney = false;
    _banknotesFailure = false;

    _success = false;
    QMap<int, int> cashOutMap;
    if (m < 50) {
        _smallAmount = true;
    } else if (m % 50 != 0) {
        _notDivisible = true;

    } else if (m >= _totalCashAmount) {
        _notEnoughMoney = true;

    } else {
        int n = m;
        int _50(0),
                _100(0),
                _200(0),
                _500(0);
        while (n >= 500 && has500(_500)) {
            _500++;
            n -= 500;
        }
        if (_500 > 0 && n % 200 != 0 && !has100()) {
            _500--;
            n += 500;
        }
        while (n >= 200 && has200(_200)) {
            _200++;
            n -= 200;
        }
        while (n >= 100 && has100(_100)) {
            _100++;
            n -= 100;
        }
        while (n >= 50 && has50(_50)) {
            _50++;
            n -= 50;
        }

        if (n != 0) {
            {
                _banknotesFailure = true;
            }
        } else {
            if (!banknotesFailure() && !notEnoughMoney() && !notDivisible()) {
                _success = true;
                cashOutMap[50] = _50;
                cashOutMap[100] = _100;
                cashOutMap[200] = _200;
                cashOutMap[500] = _500;
                QMessageBox msgBox;
                QString a = "Done successfuly!\nYour set of banknotes:\n";
                QString f = "";
                QString h = "";
                QString t = "";
                QString fi = "";
                if (_50 != 0) {
                    f = "\n50$ : " + QString::number(_50);
                }
                if (_100 != 0) {
                    h = "\n100$ : " + QString::number(_100);
                }
                if (_200 != 0) {
                    t = "\n200$ : " + QString::number(_200);
                }
                if (_500 != 0) {
                    fi = "\n500$ : " + QString::number(_500);
                }

                a = a + f + h + t + fi;
                msgBox.setText(a);
                msgBox.exec();
                updateNotesMap(cashOutMap);
                setTotalCashAmount();
            }
        }
    }
}

void SessionManager::updateNotesMap(QMap<int, int> m) {
    change50(_notesMap[50] - m[50]);
    change100(_notesMap[100] - m[100]);
    change200(_notesMap[200] - m[200]);
    change500(_notesMap[500] - m[500]);

    initialiseNotes();
}
//


void SessionManager::checkCard(QString card) {
    _numTry = 0;
    if (cardExists(card)) {
        if (!cardBlocked(card)) {
            _cardOk = true;
            _card = card;

        } else {
            _cardOk = false;
            QMessageBox::warning(NULL, QObject::tr("Error"),
                                 QObject::tr("Card is blocked!\n Please, call your banking assistant!\n"),
                                 QMessageBox::Ok);
        }
    } else {
        _cardOk = false;
        QMessageBox::warning(NULL, QObject::tr("Error"),
                             QObject::tr("Wrong card number!\n"), QMessageBox::Ok);

    }
}

void SessionManager::checkPin(QString pin) {
    if (getDepositAccountByCardAndPin(_card, pin).cardNumber() != "") {
        _da = getDepositAccountByCardAndPin(_card, pin);
        _numTry = 0;
        _isDeposit = true;
        _isCredit = false;
        _isUniversal = false;
        _cardPinOk = true;
        qWarning("deposit");
    } else if (getCreditAccountByCardAndPin(_card, pin).cardNumber() != "") {
        _numTry = 0;
        _ca = getCreditAccountByCardAndPin(_card, pin);

        _isDeposit = false;
        _isCredit = true;
        _isUniversal = false;
        _cardPinOk = true;
        qWarning("credit");
    } else if (getUniversalAccountByCardAndPin(_card, pin).cardNumber() != "") {
        _numTry = 0;
        _ua = getUniversalAccountByCardAndPin(_card, pin);
        _isDeposit = false;
        _isCredit = false;
        _isUniversal = true;
        _cardPinOk = true;
        qWarning("universal");

    } else {
        _cardPinOk = false;
        _numTry++;
        QMessageBox::warning(NULL, QObject::tr("Error"),
                             QObject::tr("Wrong PIN! Try again!\n"), QMessageBox::Ok);

    }

}

void SessionManager::putMoney(int sumPut) {

    if (_isDeposit) {
        incashMoney(sumPut);
        if (isSuccess()) {
            putMoneyOnDepositAccount(sumPut, _da);
        }
    } else if (_isCredit) {
        incashMoney(sumPut);
        if (isSuccess()) {
            putMoneyOnCreditAccount(sumPut, _ca);
        }


    } else {
        incashMoney(sumPut);
        if (isSuccess()) {

            putMoneyOnUniversalAccount(sumPut, _ua);
        }
    }
}


void SessionManager::withdrawMoney(int sumOut) {
    _limitFailure = false;
    _balanceFailure = false;
    if (_isDeposit) {
        QMessageBox::warning(NULL, QObject::tr("Error"),
                             QObject::tr("You can not withdraw money from Deposit Account!\n"), QMessageBox::Ok);
    } else if (_isCredit) {
        if (sumOut <= _ca.sumOnBalance()) {
            if (sumOut <= _ca.limit()) {
                calculateNotesOut(sumOut);
                if (isSuccess()) {
                    withdrawMoneyFromCreditAccount(sumOut, _ca);
                }
            } else {
                _limitFailure = true;
            }
        } else {
            _balanceFailure = true;
        }
    } else {
        if (sumOut <= _ua.sumOnBalance()) {
            if (sumOut <= _ua.limit()) {
                calculateNotesOut(sumOut);
                if (isSuccess()) {
                    withdrawMoneyFromUniversalAccount(sumOut, _ua);
                }
            } else {
                _limitFailure = true;
            }
        } else {
            _balanceFailure = true;
        }


    }
}


int SessionManager::getBalance() const {
    int balance;
    if (_isCredit) {
        balance = _ca.sumOnBalance();
    } else if (_isUniversal) {
        balance = _ua.sumOnBalance();
    } else if (_isDeposit) {
        balance = _da.sumOnBalance();
    }
    return balance;

}

int SessionManager::getLimit() const {
    int limit;
    if (_isCredit) {
        limit = _ca.limit();
    } else if (_isUniversal) {
        limit = _ua.limit();
    } else if (_isDeposit) {
        limit = _da.limit();
    }
    return limit;
}

void SessionManager::setLimit(int n) {
    setNewLimit(_card, n);
    if (_isCredit) {
        _ca.limit() = n;
    } else if (_isUniversal) {
        _ua.limit() = n;
    } else if (_isDeposit) {
        _da.limit() = n;
    }

}

void SessionManager::putMoneyToMyCredit(int sumOut) {
    _limitFailure = false;
    _balanceFailure = false;
    _ca = getCreditAccountByUserId(selectUserByCard(_card).id());
    if (_isUniversal) {
        if (sumOut <= _ua.sumOnBalance()) {
            if (sumOut <= _ua.limit()) {
                makeTransactionFromUniversalToCredit(_ua, _ca, sumOut);
            } else {
                _limitFailure = true;
            }
        } else {
            _balanceFailure = true;
        }
    } else {
        QMessageBox::warning(NULL, QObject::tr("Error"),
                             QObject::tr("Wrong account!\n"), QMessageBox::Ok);
    }
}

void SessionManager::putMoneyToMyUniversal(int sumOut) {
    _limitFailure = false;
    _balanceFailure = false;
    _ua = getUniversalAccountByUserId(selectUserByCard(_card).id());
    if (_isCredit) {
        if (sumOut <= _ca.sumOnBalance()) {
            if (sumOut <= _ca.limit()) {
                makeTransactionFromCreditToUniversal(_ca, _ua, sumOut);
            } else {
                _limitFailure = true;
            }
        } else {
            _balanceFailure = true;
        }
    } else {
        QMessageBox::warning(NULL, QObject::tr("Error"),
                             QObject::tr("Wrong account!\n"), QMessageBox::Ok);
    }
}

void SessionManager::putMoneyToMyDeposit(int sumOut) {
    _limitFailure = false;
    _balanceFailure = false;
    _da = getDepositAccountByUserId(selectUserByCard(_card).id());
    if (_isCredit) {
        if (sumOut <= _ca.sumOnBalance()) {
            if (sumOut <= _ca.limit()) {
                makeTransactionFromCreditToDeposit(_ca, _da, sumOut);
            } else {
                _limitFailure = true;
            }
        } else {
            _balanceFailure = true;
        }

    } else if (_isUniversal) {
        if (sumOut <= _ua.sumOnBalance()) {
            if (sumOut <= _ua.limit()) {
                makeTransactionFromUniversalDeposit(_ua, _da, sumOut);
            } else {
                _limitFailure = true;
            }
        } else {
            _balanceFailure = true;
        }
    } else {
        QMessageBox::warning(NULL, QObject::tr("Error"),
                             QObject::tr("Wrong account!\n"), QMessageBox::Ok);
    }
}


void SessionManager::putMoneyToAnother(int sumOut, QString card) {
    _limitFailure = false;
    _balanceFailure = false;
    if (_isCredit) {
        if (sumOut < _ca.sumOnBalance()) {
            if (sumOut < _ca.limit()) {
                if (cardExists(card)) {
                    makeTransactionFromCreditToAnother(_ca, card, sumOut, true);
                } else {
                    makeTransactionFromCreditToAnother(_ca, card, sumOut, false);
                }
            } else {
                _limitFailure = true;
            }
        } else {
            _balanceFailure = true;
        }
    } else if (_isUniversal) {
        if (sumOut < _ua.sumOnBalance()) {
            if (sumOut < _ua.limit()) {
                if (cardExists(card)) {
                    makeTransactionFromUniversalToAnother(_ua, card, sumOut, true);
                } else {
                    makeTransactionFromUniversalToAnother(_ua, card, sumOut, false);
                }
            } else {
                _limitFailure = true;
            }
        } else {
            _balanceFailure = true;
        }
    }
}
