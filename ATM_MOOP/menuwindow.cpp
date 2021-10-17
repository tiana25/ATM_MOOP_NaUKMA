#include "menuwindow.h"
#include "ui_menuwindow.h"
#include <QMainWindow>
#include <QProcess>

MenuWindow::MenuWindow(SessionManager sm, QWidget *parent) :
        QDialog(parent),
        _sessionManager(sm),
        ui(new Ui::MenuWindow) {
    ui->setupUi(this);
    ui->user->setText(sm.getUser());

}

MenuWindow::~MenuWindow() {
    delete ui;
}

void MenuWindow::on_end_session_clicked() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MenuWindow::on_put_money_clicked() {
    hide();
    putmoneywindow = new PutMoneyWindow(_sessionManager, this);
    putmoneywindow->exec();
    show();
}

void MenuWindow::on_cash_withdraw_clicked() {
    hide();
    withdrawalwindow = new WithdrawalWindow(_sessionManager, this);
    withdrawalwindow->exec();
    show();
}

void MenuWindow::on_transfer_to_mycard_clicked() {
    if (_sessionManager.isCredit()) {
        if (getDepositAccountByUserId(_sessionManager.getCreditAccount().userId()).cardNumber().isNull() &&
            getUniversalAccountByUserId(_sessionManager.getCreditAccount().userId()).cardNumber().isNull()) {

            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("You do not have other accounts!\n"), QMessageBox::Ok);

        } else {

            hide();
            putmoneytomyaccount = new PutMoneyToMyAccount(_sessionManager, this);
            putmoneytomyaccount->exec();
            show();
        }
    } else if (_sessionManager.isUniversal()) {
        if (getCreditAccountByUserId(_sessionManager.getUniversalAccount().userId()).cardNumber().isNull() &&
            getDepositAccountByUserId(_sessionManager.getUniversalAccount().userId()).cardNumber().isNull()) {

            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("You do not have other accounts!\n"), QMessageBox::Ok);

        } else {

            hide();
            putmoneytomyaccount = new PutMoneyToMyAccount(_sessionManager, this);
            putmoneytomyaccount->exec();
            show();
        }
    }

}

void MenuWindow::on_transfer_to_anothercard_clicked() {
    hide();
    putmoneytoanotheraccount = new PutMoneyToAnotherAccount(_sessionManager, this);
    putmoneytoanotheraccount->exec();
    show();
}

void MenuWindow::on_balance_inquiry_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your balance is:\n";
    a += QString::number(_sessionManager.getBalance());
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindow::on_transaction_history_clicked() {
    transactionhistorywindow = new TransactionHistoryWindow(_sessionManager, this);
    hide();
    transactionhistorywindow->exec();
    show();
}

void MenuWindow::on_deposit_clicked() {
    hide();
    setlimitwindow = new SetLimitWindow(_sessionManager, this);
    setlimitwindow->exec();
    show();
}

void MenuWindow::on_showLimit_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your limit is:\n";
    a += QString::number(_sessionManager.getLimit());
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindow::on_cardexp_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your card expiry date is:\n";

    a += _sessionManager.getUniversalAccount().expiryDate();
    msgBox.setText(a);
    msgBox.exec();
}
