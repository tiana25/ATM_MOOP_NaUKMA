#ifndef STARBANKATM_MOOP_KMA_CREDITACCOUNT_H
#define STARBANKATM_MOOP_KMA_CREDITACCOUNT_H
#include "Account.h"
class CreditAccount : public Account{
private:
    size_t _creditTerm;
    double _creditDept;
    string _creditExpiryDate;
public:
    CreditAccount(){
		_creditDept = 0;
		_creditTerm = 0;

	}
    CreditAccount(size_t creditTerm, double creditDept, size_t userIdATM, string cardNumber, string pin, string cvv, double sumOnBalance, size_t limit, bool isBlocked, string expiryDate, string creditExpiryDate = "");
    ~CreditAccount();
    CreditAccount& operator=(const CreditAccount&);

    size_t& creditTerm();
    double& creditDept();
    string& creditExpiryDate();

    const size_t& creditTerm() const;
    const double& creditDept() const;
    const string& creditExpiryDate() const;

    void putMoney(double amount) override;
    void close();
    void withdrawMoney(size_t amount);
    void openNew(size_t creditTerm, double creditDept);
};
ostream& operator<<(ostream& os, const CreditAccount& acc);
#endif //STARBANKATM_MOOP_KMA_CREDITACCOUNT_H
