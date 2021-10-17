#ifndef PUTMONEYWINDOW_H
#define PUTMONEYWINDOW_H
#pragma once

#include <QDialog>
#include "SessionManager.h"
#include "question.h"

namespace Ui {
    class PutMoneyWindow;
}

class PutMoneyWindow : public QDialog {
    Q_OBJECT

public:
    explicit PutMoneyWindow(SessionManager, QWidget *parent = nullptr);

    ~PutMoneyWindow();

private
    slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    int _sum = 0;
    SessionManager _sessionManager;
    Ui::PutMoneyWindow *ui;
    Question *questionwindow;
};

#endif // PUTMONEYWINDOW_H
