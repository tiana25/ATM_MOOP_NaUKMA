#ifndef PASSWORDWINDOW_H
#define PASSWORDWINDOW_H
#pragma once

#include <QDialog>
#include <QMessageBox>
#include "menuwindow.h"
#include "menuwindowcredit.h"
#include "menuwindowdeposit.h"
#include "SessionManager.h"

namespace Ui {
    class PasswordWindow;
}

class PasswordWindow : public QDialog {
    Q_OBJECT

public:

    explicit PasswordWindow(SessionManager, QWidget *parent = nullptr);

    ~PasswordWindow();

private:
    Ui::PasswordWindow *ui;
    MenuWindow *menuwindow;
    MenuWindowCredit *menuwindowcredit;
    MenuWindowDeposit *menuwindowdeposit;
    QString _pin;
    SessionManager _sessionManager;

private
    slots:
    void digit_numbers();

    void on_digit_back_clicked();

    void on_digit_OK_clicked();

    void on_pushButton_clicked();
};

#endif // PASSWORDWINDOW_H
