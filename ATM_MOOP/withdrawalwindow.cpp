#include "withdrawalwindow.h"
#include "ui_withdrawalwindow.h"
#include <QProcess>
#include "passwordwindow.h"
#include "mainwindow.h"

WithdrawalWindow::WithdrawalWindow(SessionManager sm, QWidget *parent) :
        _sessionManager(sm),
        QDialog(parent),
        ui(new Ui::WithdrawalWindow) {

    ui->setupUi(this);
    ui->user->setText(sm.getUser());
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

void WithdrawalWindow::digit_numbers() {
    QPushButton *digit = (QPushButton *) sender();

    QString _cardNum;

    _cardNum = ui->amount->text() + digit->text();

    ui->amount->setText(_cardNum);
}

WithdrawalWindow::~WithdrawalWindow() {
    delete ui;
}


void WithdrawalWindow::on_pushButton_5_clicked() {
    this->close();
}


void WithdrawalWindow::on_pushButton_clicked() {
    _sessionManager.withdrawMoney(50);
    if (_sessionManager.balanceFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("You do not have enough money!\n"), QMessageBox::Ok);
    } else if (_sessionManager.limitFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Amount is more than your limit!\n"), QMessageBox::Ok);
    } else if (_sessionManager.banknotesFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("ATM hasn't required set of banknotes!\n"), QMessageBox::Ok);
    } else if (_sessionManager.smallAmount()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount that is more than 50!\n"), QMessageBox::Ok);
    } else if (_sessionManager.notDivisible()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount that is divisible by 50\n"), QMessageBox::Ok);
    } else {

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
}

//100
void WithdrawalWindow::on_pushButton_2_clicked() {
    _sessionManager.withdrawMoney(100);
    if (_sessionManager.balanceFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("You do not have enough money!\n"), QMessageBox::Ok);
    } else if (_sessionManager.limitFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Amount is more than your limit!\n"), QMessageBox::Ok);
    } else if (_sessionManager.banknotesFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("ATM hasn't required set of banknotes!\n"), QMessageBox::Ok);
    } else if (_sessionManager.smallAmount()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount that is more than 50!\n"), QMessageBox::Ok);
    } else if (_sessionManager.notDivisible()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount that is divisible by 50\n"), QMessageBox::Ok);
    } else {

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
}


void WithdrawalWindow::on_pushButton_3_clicked() {
    _sessionManager.withdrawMoney(200);
    if (_sessionManager.balanceFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("You do not have enough money!\n"), QMessageBox::Ok);
    } else if (_sessionManager.limitFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Amount is more than your limit!\n"), QMessageBox::Ok);
    } else if (_sessionManager.banknotesFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("ATM hasn't required set of banknotes!\n"), QMessageBox::Ok);
    } else if (_sessionManager.smallAmount()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount that is more than 50!\n"), QMessageBox::Ok);
    } else if (_sessionManager.notDivisible()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount that is divisible by 50\n"), QMessageBox::Ok);
    } else {

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
}


void WithdrawalWindow::on_pushButton_4_clicked() {
    _sessionManager.withdrawMoney(500);
    if (_sessionManager.balanceFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("You do not have enough money!\n"), QMessageBox::Ok);
    } else if (_sessionManager.limitFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Amount is more than your limit!\n"), QMessageBox::Ok);
    } else if (_sessionManager.banknotesFailure()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("ATM hasn't required set of banknotes!\n"), QMessageBox::Ok);
    } else if (_sessionManager.smallAmount()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount that is more than 50!\n"), QMessageBox::Ok);
    } else if (_sessionManager.notDivisible()) {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount that is divisible by 50\n"), QMessageBox::Ok);
    } else {

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
}

void WithdrawalWindow::on_digit_OK_clicked() {
    QString s = ui->amount->text();
    if (!s.isEmpty()) {
        _sessionManager.withdrawMoney(s.toInt());
        if (_sessionManager.balanceFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("You do not have enough money!\n"), QMessageBox::Ok);
        } else if (_sessionManager.limitFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("Amount is more than your limit!\n"), QMessageBox::Ok);
        } else if (_sessionManager.banknotesFailure()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("ATM hasn't required set of banknotes!\n"), QMessageBox::Ok);
        } else if (_sessionManager.smallAmount()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("Enter amount that is more than 50!\n"), QMessageBox::Ok);
        } else if (_sessionManager.notDivisible()) {
            ui->amount->setText("");
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("Enter amount that is divisible by 50\n"), QMessageBox::Ok);
        } else {

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
                             QObject::tr("Eneter amount to withdraw or choose from menu!\n"), QMessageBox::Ok);
    }
}

void WithdrawalWindow::on_digit_back_clicked() {
    QString s;
    s = ui->amount->text();
    s.resize(s.size() - 1);

    ui->amount->setText(s);
}
