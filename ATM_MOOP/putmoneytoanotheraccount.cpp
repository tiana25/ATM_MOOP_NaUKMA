#include "putmoneytoanotheraccount.h"
#include "ui_putmoneytoanotheraccount.h"
#include "passwordwindow.h"
#include <QProcess>

PutMoneyToAnotherAccount::PutMoneyToAnotherAccount(SessionManager sm, QWidget *parent) :
        _sessionManager(sm),
        QDialog(parent),
        ui(new Ui::PutMoneyToAnotherAccount) {
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

PutMoneyToAnotherAccount::~PutMoneyToAnotherAccount() {
    delete ui;
}

void PutMoneyToAnotherAccount::on_digit_back_clicked() {
    QString s;
    if (_n == 1) {
        s = ui->amount->text();
        s.resize(s.size() - 1);

        ui->amount->setText(s);
    } else {
        s = ui->card_number->text();
        s.resize(s.size() - 1);

        ui->card_number->setText(s);
    }

}

void PutMoneyToAnotherAccount::on_digit_OK_clicked() {
    if (!ui->amount->text().isEmpty() && !ui->card_number->text().isEmpty()) {
        QString s = ui->amount->text();
        QString card = ui->card_number->text();
        if(s.toInt()==0){
               ui->amount->setText("");
            _n = 1;
            QMessageBox::warning(this, QObject::tr("Error"),
                                 QObject::tr("Enter amount that is more than 0!\n"), QMessageBox::Ok);
        }else{
        if(card != _sessionManager.getCard()){
        if (cardExists(card)) {
            _sessionManager.putMoneyToAnother(s.toInt(), card);
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
                a += "$ to card of StarBank: ";
                a += card;
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
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Question", "Do you want to transfer\n to card of another bank?",
                                          QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                _sessionManager.putMoneyToAnother(s.toInt(), card);
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
                    a += "$ to card of another bank: ";
                    a += card;
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
                ui->amount->setText("");
                ui->card_number->setText("");
            }
        }
      }else {
             QMessageBox::warning(this, QObject::tr("Error"),
                                  QObject::tr("You can't make a transaction to the current card!\n"), QMessageBox::Ok);
         }
        }
    } else if (ui->amount->text().isEmpty()) {
        _n = 1;
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter amount to transfer!\n"), QMessageBox::Ok);
    } else if (ui->card_number->text().isEmpty()) {
        _n = 2;
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter card number\nyou want to transfer money to!\n"), QMessageBox::Ok);
    }

}

void PutMoneyToAnotherAccount::digit_numbers() {
    QPushButton *digit = (QPushButton *) sender();

    QString s;
    if (_n == 1) {


        s = ui->amount->text() + digit->text();

        ui->amount->setText(s);
    } else {
        s = ui->card_number->text() + digit->text();

        ui->card_number->setText(s);
    }
}

void PutMoneyToAnotherAccount::on_pushButton_2_clicked() {
    this->close();
}


void PutMoneyToAnotherAccount::on_edit2_clicked() {
    _n = 2;
}

void PutMoneyToAnotherAccount::on_edit_clicked() {
    _n = 1;
}
