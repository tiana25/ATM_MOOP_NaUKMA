#ifndef MENUWINDOW_H
#define MENUWINDOW_H
#pragma once

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
    class MenuWindow;
}

class MenuWindow : public QDialog {
    Q_OBJECT

public:
    explicit MenuWindow(SessionManager, QWidget *parent = nullptr);

    ~MenuWindow();

private
    slots:

    void on_end_session_clicked();

    void on_put_money_clicked();

    void on_cash_withdraw_clicked();

    void on_transfer_to_mycard_clicked();

    void on_transfer_to_anothercard_clicked();

    void on_balance_inquiry_clicked();

    void on_transaction_history_clicked();

    void on_deposit_clicked();

    void on_showLimit_clicked();

    void on_cardexp_clicked();

private:
    Ui::MenuWindow *ui;
    WithdrawalWindow *withdrawalwindow;
    PutMoneyWindow *putmoneywindow;
    SessionManager _sessionManager;
    Question *questionwindow;
    SetLimitWindow *setlimitwindow;
    TransactionHistoryWindow *transactionhistorywindow;
    PutMoneyToAnotherAccount *putmoneytoanotheraccount;
    PutMoneyToMyAccount *putmoneytomyaccount;
};

#endif // MENUWINDOW_H
