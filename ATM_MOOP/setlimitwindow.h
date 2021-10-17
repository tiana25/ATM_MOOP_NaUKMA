#ifndef SETLIMITWINDOW_H
#define SETLIMITWINDOW_H
#pragma once

#include <QDialog>
#include "SessionManager.h"
#include "question.h"

namespace Ui {
    class SetLimitWindow;
}

class SetLimitWindow : public QDialog {
    Q_OBJECT

public:
    explicit SetLimitWindow(SessionManager, QWidget *parent = nullptr);

    ~SetLimitWindow();

private
    slots:
    void on_digit_OK_clicked();

    void digit_numbers();

    void on_digit_back_clicked();

    void on_returnFromSetLimit_clicked();

private:
    Ui::SetLimitWindow *ui;
    SessionManager _sessionManager;
    Question *questionwindow;
};

#endif // SETLIMITWINDOW_H
