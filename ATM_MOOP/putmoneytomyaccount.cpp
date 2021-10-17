#include "putmoneytomyaccount.h"
#include "ui_putmoneytomyaccount.h"
#include "passwordwindow.h"
#include<QProcess>

PutMoneyToMyAccount::PutMoneyToMyAccount(SessionManager sm, QWidget *parent) :
        _sessionManager(sm),
        QDialog(parent),

        ui(new Ui::PutMoneyToMyAccount) {
    ui->setupUi(this);
    ui->user->setText(sm.getUser());
    ui->credit->setEnabled(false);
    ui->deposit->setEnabled(false);
    ui->universal->setEnabled(false);
    connect(ui->digit_1, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_2, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_3, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_4, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_5, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_6, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_7, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_8, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_9, SIGNAL(clicked()), this, SLOT(digit_numbers()));
    connect(ui->digit_0, SIGNAL(clicked()), this, SLOT(digit_numbers()));
}

void PutMoneyToMyAccount::digit_numbers() {
    QPushButton *digit = (QPushButton *) sender();

    QString s;

    s = ui->amount->text() + digit->text();

    ui->amount->setText(s);
}

PutMoneyToMyAccount::~PutMoneyToMyAccount() {
    delete ui;
}


void PutMoneyToMyAccount::on_deposit_clicked() {
    QString s = ui->amount->text();
    if (!s.isEmpty()) {

        _sessionManager.putMoneyToMyDeposit(s.toInt());
        if (_sessionManager.limitFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("Amount is more than your limit!\n"), QMessageBox::Ok);
        } else if (_sessionManager.balanceFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("You do not have enough money!\n"), QMessageBox::Ok);
        } else {
            QMessageBox msgBox(this);
            QString a = "Transfered successfully:\n";
            a += s;
            a += "$ to card: ";
            a += _da.cardNumber();
            msgBox.setText(a);
            msgBox.exec();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Question", "Do you want to continue?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                hide();

            } else {
                qApp->quit();
                QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

            }
        }

    } else {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Eneter amount to transfer!\n"), QMessageBox::Ok);
    }
}


void PutMoneyToMyAccount::on_universal_clicked() {

    QString s = ui->amount->text();
    if (!s.isEmpty()) {
        _sessionManager.putMoneyToMyUniversal(s.toInt());
        if (_sessionManager.limitFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("Amount is more than your limit!\n"), QMessageBox::Ok);
        } else if (_sessionManager.balanceFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("You do not have enough money!\n"), QMessageBox::Ok);
        } else {
            QMessageBox msgBox(this);
            QString a = "Transfered successfully:\n";
            a += s;
            a += "$ to card: ";
            a += _ua.cardNumber();
            msgBox.setText(a);
            msgBox.exec();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Question", "Do you want to continue?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                hide();

            } else {
                qApp->quit();
                QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

            }
        }
    } else {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Eneter amount to transfer!\n"), QMessageBox::Ok);
    }
}


void PutMoneyToMyAccount::on_credit_clicked() {
    QString s = ui->amount->text();
    if (!s.isEmpty()) {
        _sessionManager.putMoneyToMyCredit(s.toInt());
        if (_sessionManager.limitFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("Amount is more than your limit!\n"), QMessageBox::Ok);
        } else if (_sessionManager.balanceFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("You do not have enough money!\n"), QMessageBox::Ok);
        } else {
            QMessageBox msgBox(this);
            QString a = "Transfered successfully:\n";
            a += s;
            a += "$ to card: ";
            a += _ca.cardNumber();
            msgBox.setText(a);
            msgBox.exec();

            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Question", "Do you want to continue?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                hide();

            } else {
                qApp->quit();
                QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

            }
        }
    } else {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Eneter amount to transfer!\n"), QMessageBox::Ok);
    }
}

void PutMoneyToMyAccount::on_digit_back_clicked() {
    QString s;
    s = ui->amount->text();
    s.resize(s.size() - 1);

    ui->amount->setText(s);
}

void PutMoneyToMyAccount::on_digit_OK_clicked() {
     QString s = ui->amount->text();
    if(s.toInt()==0){
         ui->amount->setText("");
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Eneter amount that is more than 0!\n"), QMessageBox::Ok);
    }else{
    if (_sessionManager.isCredit()) {
        if (!getDepositAccountByUserId(_sessionManager.getCreditAccount().userId()).cardNumber().isNull()) {
            _da = getDepositAccountByUserId(_sessionManager.getCreditAccount().userId());
            if (!cardBlocked(_da.cardNumber()) && depositIsValid(_da)) {

                ui->deposit->setEnabled(true);
            }

        }
        if (!getUniversalAccountByUserId(_sessionManager.getCreditAccount().userId()).cardNumber().isNull()) {
            _ua = getUniversalAccountByUserId(_sessionManager.getCreditAccount().userId());
            if (!cardBlocked(_ua.cardNumber()) && universalIsValid(_ua)) {

                ui->universal->setEnabled(true);
            }

        } else {
            QMessageBox::warning(NULL, QObject::tr("Error"),
                                 QObject::tr("You do not have other accounts\n"), QMessageBox::Ok);
        }

    } else {
        if (!getCreditAccountByUserId(_sessionManager.getUniversalAccount().userId()).cardNumber().isNull()) {

            _ca = getCreditAccountByUserId(_sessionManager.getUniversalAccount().userId());
            if (!cardBlocked(_ca.cardNumber()) && creditIsValid(_ca)) {

                ui->credit->setEnabled(true);
            }
        }
        if (!getDepositAccountByUserId(_sessionManager.getUniversalAccount().userId()).cardNumber().isNull()) {

            _da = getDepositAccountByUserId(_sessionManager.getUniversalAccount().userId());
            if (!cardBlocked(_da.cardNumber()) && depositIsValid(_da)) {

                ui->deposit->setEnabled(true);
            }
        } else {
            QMessageBox::warning(NULL, QObject::tr("Error"),
                                 QObject::tr("You do not have other accounts\n"), QMessageBox::Ok);
        }
    }
}
}

void PutMoneyToMyAccount::on_pushButton_5_clicked() {
    this->close();
}

