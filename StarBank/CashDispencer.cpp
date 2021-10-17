#include "CashDispencer.h"

CashDispencer::CashDispencer(ATM& atm)
        : _atm(atm) {
    initialiseNotes();
}


CashDispencer::~CashDispencer() {}


bool CashDispencer::isCorrectAmount(int n) {
    if (n % 50 == 0 && n >= CashDispencer::_MIN_AMOUNT && n <= _totalCashAmount) {
        return true;
    }
    else {
        return false;
    }

}
void CashDispencer::initialiseNotes() {
    _notesMap[50] = 100;
    _notesMap[100] = 100;
    _notesMap[200] = 100;
    _notesMap[500] = 100;
    _amountOk=false;
    setTotalCashAmount();
}

void CashDispencer::setTotalCashAmount() {
    int total = 0;
    total += _notesMap[50] * 50;
    total += _notesMap[100] * 100;
    total += _notesMap[200] * 200;
    total += _notesMap[500] * 500;
    _totalCashAmount = total;
}

const map<int, int> CashDispencer::calculateNotesOut(const int m) {
    map<int, int> cashOutMap;
    if (!isCorrectAmount(m)) {
        _amountOk=false;
       cout<<"Please enter amount that is divisible by 50! "<<endl;
    }
    else {
        int n = m;
        int amount = m;
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
            _amountOk = false;
            cout << "ATM hasn't required set of banknotes: " << amount << endl;
        }
        else {
            cashOutMap[50] = _50;
            cashOutMap[100] = _100;
            cashOutMap[200] = _200;
            cashOutMap[500] = _500;
            _amountOk = true;
            return cashOutMap;
        }
    }
    return cashOutMap;
   
}

void CashDispencer::updateNotesMap(map<int, int> m) {
    _notesMap[50] = _notesMap[50] - m[50];
    _notesMap[100] = _notesMap[100] - m[100];
    _notesMap[200] = _notesMap[200] - m[200];
    _notesMap[500] = _notesMap[500] - m[500];
}
void CashDispencer::getNotesOut(const int n) {
            map<int, int> notesOutMap(calculateNotesOut(n));
            updateNotesMap(notesOutMap);
            setTotalCashAmount();
            map<int, int>::iterator it;
            for (it = notesOutMap.begin(); it != notesOutMap.end(); it++) {
                if (it->second) {
                    cout << it->first  // key
                        << " UAH:"
                        << it->second   // value
                        << std::endl;
                }
            }
}

void CashDispencer::incashMoney(int n) {
    if(n!=50 && n!=100 && n!=200 && n!=500){
        _wrongBanknote=true;
        cout<<"Wrong banknote! Try again!"<<endl;
	}
	else {
		_notesMap[n]++;
		setTotalCashAmount();
		_blocked = false;
	    _wrongBanknote=false;
	}
    
}

