#ifndef PUTMONEYTOMYACCOUNT_H
#define PUTMONEYTOMYACCOUNT_H
#pragma once

#include <QDialog>
#include "SessionManager.h"
#include "question.h"

namespace Ui {
    class PutMoneyToMyAccount;
}

class PutMoneyToMyAccount : public QDialog {
    Q_OBJECT

public:
    explicit PutMoneyToMyAccount(SessionManager, QWidget *parent = nullptr);

    ~PutMoneyToMyAccount();

private
    slots:
    void digit_numbers();

    void on_digit_back_clicked();

    void on_digit_OK_clicked();

    void on_pushButton_5_clicked();

    void on_deposit_clicked();

    void on_credit_clicked();

    void on_universal_clicked();

private:
    DepositAccount _da;
    CreditAccount _ca;
    UniversalAccount _ua;
    Ui::PutMoneyToMyAccount *ui;
    SessionManager _sessionManager;
    Question *questionwindow;
};

#endif // PUTMONEYTOMYACCOUNT_H
