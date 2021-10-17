#include "menuwindowdeposit.h"
#include "ui_menuwindowdeposit.h"
#include<QProcess>

MenuWindowDeposit::MenuWindowDeposit(SessionManager sm, QWidget *parent) :
        _sessionManager(sm),
        QDialog(parent),
        ui(new Ui::MenuWindowDeposit) {
    ui->setupUi(this);
    ui->user->setText(sm.getUser());
}

MenuWindowDeposit::~MenuWindowDeposit() {
    delete ui;
}

void MenuWindowDeposit::on_end_session_clicked() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MenuWindowDeposit::on_put_money_clicked() {
    hide();
    putmoneywindow = new PutMoneyWindow(_sessionManager, this);
    putmoneywindow->exec();
    show();
}

void MenuWindowDeposit::on_balance_inquiry_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your balance is:\n";
    a += QString::number(_sessionManager.getBalance());
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindowDeposit::on_transaction_history_clicked() {
    transactionhistorywindow = new TransactionHistoryWindow(_sessionManager, this);
    hide();
    transactionhistorywindow->exec();
    show();
}

void MenuWindowDeposit::on_deposit_clicked() {
    hide();
    setlimitwindow = new SetLimitWindow(_sessionManager, this);
    setlimitwindow->exec();
    show();
}

void MenuWindowDeposit::on_showLimit_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your limit is:\n";
    a += QString::number(_sessionManager.getLimit());
    msgBox.setText(a);
    msgBox.exec();
}


void MenuWindowDeposit::on_creditterm_clicked() {
    QMessageBox msgBox(this);
    int time = _sessionManager.getDepositAccount().depositTerm();
    int day = time / 24 / 3600;
    int hours = time / 3600 - day * 24;
    msgBox.setText("Your deposit term is:\n" + QString::number(day) + " days " + QString::number(hours) + " hours ");
    msgBox.exec();
}

void MenuWindowDeposit::on_perc_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your deposit percentage is:\n %";
    a += QString::number(_sessionManager.getDepositAccount().depositPercentage());
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindowDeposit::on_exp_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your deposit expiry date is:\n";
    a += _sessionManager.getDepositAccount().depositExpiryDate();
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindowDeposit::on_cardexp_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your card expiry date is:\n";
    a += _sessionManager.getDepositAccount().expiryDate();
    msgBox.setText(a);
    msgBox.exec();
}
