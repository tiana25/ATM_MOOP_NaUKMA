#ifndef MENUWINDOWDEPOSIT_H
#define MENUWINDOWDEPOSIT_H

#include <QDialog>
#include <QMessageBox>
#include "SessionManager.h"
#include "withdrawalwindow.h"
#include "putmoneywindow.h"
#include "question.h"
#include "setlimitwindow.h"
#include "transactionhistorywindow.h"
#include "putmoneytoanotheraccount.h"
#include "putmoneytomyaccount.h"

namespace Ui {
    class MenuWindowDeposit;
}

class MenuWindowDeposit : public QDialog {
    Q_OBJECT

public:
    explicit MenuWindowDeposit(SessionManager, QWidget *parent = nullptr);

    ~MenuWindowDeposit();

private
    slots:

    void on_put_money_clicked();

    void on_balance_inquiry_clicked();

    void on_transaction_history_clicked();

    void on_showLimit_clicked();

    void on_deposit_clicked();

    void on_end_session_clicked();

    void on_creditterm_clicked();

    void on_perc_clicked();

    void on_exp_clicked();

    void on_cardexp_clicked();

private:
    Ui::MenuWindowDeposit *ui;
    WithdrawalWindow *withdrawalwindow;
    PutMoneyWindow *putmoneywindow;
    SessionManager _sessionManager;
    Question *questionwindow;
    SetLimitWindow *setlimitwindow;
    TransactionHistoryWindow *transactionhistorywindow;
    PutMoneyToAnotherAccount *putmoneytoanotheraccount;
    PutMoneyToMyAccount *putmoneytomyaccount;
};

#endif // MENUWINDOWDEPOSIT_H
