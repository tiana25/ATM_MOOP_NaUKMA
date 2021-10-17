#include <iostream>
#include <map>
using namespace std;

class ATM;
class CashDispencer
{
private:
    bool _blocked = false;
    bool _amountOk = false;
    bool _wrongBanknote = false;
    static const int _MIN_AMOUNT = 50;
    int _totalCashAmount;
    map<int, int> _notesMap;
    ATM& _atm;
    CashDispencer(const CashDispencer&);
    CashDispencer& operator=
            (const CashDispencer&);

    bool has50(int x = 0) { return _notesMap[50] - x > 0; }
    bool has100(int x = 0) { return _notesMap[100] - x > 0; }
    bool has200(int x = 0) { return _notesMap[200] - x > 0; }
    bool has500(int x = 0) { return _notesMap[500] - x > 0; }
    void initialiseNotes();
    void setTotalCashAmount();
    const map<int, int> calculateNotesOut(const int);
    void updateNotesMap(map<int, int>);

public:
    class BadAmount;
    CashDispencer(ATM&);
    ~CashDispencer();
    bool wrongBanknote(){return _wrongBanknote;}
    bool amountIsOk(){return _amountOk;}
    bool isBlocked() { return _blocked; } // if is blocked - we cant withdraw money
    bool isCorrectAmount(int);
    int getTotalCashAmount() const { return _totalCashAmount; }

    void incashMoney(int);

    void getNotesOut(const int);

    //get how much money we have in ATM
    const map<int, int> howMuchMoneyAtmHas() { return _notesMap; }
};
