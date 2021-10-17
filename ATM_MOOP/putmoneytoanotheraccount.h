#ifndef PUTMONEYTOANOTHERACCOUNT_H
#define PUTMONEYTOANOTHERACCOUNT_H
#pragma once

#include <QDialog>
#include "SessionManager.h"
#include "question.h"

namespace Ui {
    class PutMoneyToAnotherAccount;
}

class PutMoneyToAnotherAccount : public QDialog {
    Q_OBJECT

public:
    explicit PutMoneyToAnotherAccount(SessionManager, QWidget *parent = nullptr);

    ~PutMoneyToAnotherAccount();

private
    slots:
    void on_digit_back_clicked();

    void on_digit_OK_clicked();

    void digit_numbers();

    void on_pushButton_2_clicked();


    void on_edit2_clicked();

    void on_edit_clicked();

private:
    int _n = 1;
    Ui::PutMoneyToAnotherAccount *ui;
    SessionManager _sessionManager;
    Question *questionwindow;
};

#endif // PUTMONEYTOANOTHERACCOUNT_H
