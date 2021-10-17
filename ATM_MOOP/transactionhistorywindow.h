#ifndef TRANSACTIONHISTORYWINDOW_H
#define TRANSACTIONHISTORYWINDOW_H
#pragma once

#include "SessionManager.h"
#include <QDialog>

namespace Ui {
    class TransactionHistoryWindow;
}

class TransactionHistoryWindow : public QDialog {
    Q_OBJECT

public:
    explicit TransactionHistoryWindow(SessionManager, QWidget *parent = nullptr);

    ~TransactionHistoryWindow();

private
    slots:
            void on_pushButton_6_clicked();

    void on_pushButton_clicked();

private:
    Ui::TransactionHistoryWindow *ui;
    SessionManager _sessionManager;
};

#endif // TRANSACTIONHISTORYWINDOW_H
