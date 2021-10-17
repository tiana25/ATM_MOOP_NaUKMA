#include "menuwindowcredit.h"
#include "ui_menuwindowcredit.h"
#include <QProcess>

MenuWindowCredit::MenuWindowCredit(SessionManager sm, QWidget *parent) :
        _sessionManager(sm),
        QDialog(parent),
        ui(new Ui::MenuWindowCredit) {
    ui->setupUi(this);
    ui->user->setText(sm.getUser());
}

MenuWindowCredit::~MenuWindowCredit() {
    delete ui;
}

void MenuWindowCredit::on_end_session_clicked() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MenuWindowCredit::on_put_money_clicked() {
    hide();
    putmoneywindow = new PutMoneyWindow(_sessionManager, this);
    putmoneywindow->exec();
    show();
}

void MenuWindowCredit::on_cash_withdraw_clicked() {
    hide();
    withdrawalwindow = new WithdrawalWindow(_sessionManager, this);
    withdrawalwindow->exec();
    show();
}

void MenuWindowCredit::on_transfer_to_mycard_clicked() {
    if (_sessionManager.isCredit()) {
        if (getDepositAccountByUserId(_sessionManager.getCreditAccount().userId()).cardNumber().isNull() &&
            getUniversalAccountByUserId(_sessionManager.getCreditAccount().userId()).cardNumber().isNull()) {

            QMessageBox::warning(NULL, QObject::tr("Error"),
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

            QMessageBox::warning(NULL, QObject::tr("Error"),
                                 QObject::tr("You do not have other accounts!\n"), QMessageBox::Ok);

        } else {

            hide();
            putmoneytomyaccount = new PutMoneyToMyAccount(_sessionManager, this);
            putmoneytomyaccount->exec();
            show();
        }
    }

}

void MenuWindowCredit::on_transfer_to_anothercard_clicked() {
    hide();
    putmoneytoanotheraccount = new PutMoneyToAnotherAccount(_sessionManager, this);
    putmoneytoanotheraccount->exec();
    show();
}

void MenuWindowCredit::on_balance_inquiry_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your balance is:\n";
    a += QString::number(_sessionManager.getBalance());
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindowCredit::on_transaction_history_clicked() {
    transactionhistorywindow = new TransactionHistoryWindow(_sessionManager, this);
    hide();
    transactionhistorywindow->exec();
    show();
}

void MenuWindowCredit::on_deposit_clicked() {
    hide();
    setlimitwindow = new SetLimitWindow(_sessionManager, this);
    setlimitwindow->exec();
    show();
}

void MenuWindowCredit::on_showLimit_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your limit is:\n";
    a += QString::number(_sessionManager.getLimit());
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindowCredit::on_creditterm_clicked() {
    QMessageBox msgBox(this);
    int time = _sessionManager.getCreditAccount().creditTerm();
    int day = time / 24 / 3600;
    int hours = time / 3600 - day * 24;
    msgBox.setText("Your credit term is:\n" + QString::number(day) + " days " + QString::number(hours) + " hours");
    msgBox.exec();
}

void MenuWindowCredit::on_creditexp_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your credit expiry date is:\n";
    a += _sessionManager.getCreditAccount().creditExpiryDate();
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindowCredit::on_creditdept_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your credit dept is:\n";
    a += QString::number(_sessionManager.getCreditAccount().creditDept());
    msgBox.setText(a);
    msgBox.exec();
}

void MenuWindowCredit::on_cardexp_clicked() {
    QMessageBox msgBox(this);
    QString a = "Your card expiry date is:\n";
    a += _sessionManager.getCreditAccount().expiryDate();
    msgBox.setText(a);
    msgBox.exec();
}
