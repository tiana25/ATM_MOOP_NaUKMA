#ifndef WITHDRAWALWINDOW_H
#define WITHDRAWALWINDOW_H
#pragma once

#include "SessionManager.h"
#include <QDialog>
#include "question.h"

namespace Ui {
    class WithdrawalWindow;
}

class WithdrawalWindow : public QDialog {
    Q_OBJECT

public:
    explicit WithdrawalWindow(SessionManager, QWidget *parent = nullptr);

    ~WithdrawalWindow();

private
    slots:
    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void digit_numbers();

    void on_digit_OK_clicked();

    void on_digit_back_clicked();

private:
    SessionManager _sessionManager;
    Ui::WithdrawalWindow *ui;
    Question *questionwindow;

};

#endif // WITHDRAWALWINDOW_H
