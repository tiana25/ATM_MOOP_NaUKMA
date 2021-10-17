#include "passwordwindow.h"
#include "ui_passwordwindow.h"
#include <QAction>
#include <QProcess>
#include <QtDebug>

PasswordWindow::PasswordWindow(SessionManager sm, QWidget *parent) :
        _sessionManager(sm), QDialog(parent),
        ui(new Ui::PasswordWindow), _pin("") {
    sm.initialiseNotes();
    ui->setupUi(this);

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


PasswordWindow::~PasswordWindow() {
    delete ui;
}

void PasswordWindow::digit_numbers() {
    QPushButton *digit = (QPushButton *) sender();

    QString _cardPinShowed;

    _pin += digit->text();
    _cardPinShowed = ui->card_pin->text() + "*";

    ui->card_pin->setText(_cardPinShowed);
}

void PasswordWindow::on_digit_back_clicked() {
    QString _cardPin;
    _cardPin = ui->card_pin->text();
    _cardPin.resize(_cardPin.size() - 1);
    _pin.resize(_pin.size() - 1);
    ui->card_pin->setText(_cardPin);
}

void PasswordWindow::on_digit_OK_clicked() {
    if (!_pin.isEmpty()) {
        _sessionManager.checkPin(_pin);
        if (_sessionManager.cardPinIsOk()) {

            if (_sessionManager.isCredit()) {
                hide();
                menuwindowcredit = new MenuWindowCredit(_sessionManager, this);
                menuwindowcredit->show();
            } else if (_sessionManager.isDeposit()) {
                hide();
                menuwindowdeposit = new MenuWindowDeposit(_sessionManager, this);
                menuwindowdeposit->show();
            } else if (_sessionManager.isUniversal()) {
                hide();
                menuwindow = new MenuWindow(_sessionManager, this);
                menuwindow->show();
            }

        } else {
            if (_sessionManager.getTry() > 2) {

                blockCard(_sessionManager.getActiveCardNumber());
                QMessageBox::warning(NULL, QObject::tr("Sorry"),
                                     QObject::tr("There are no attempts left.\nYour card is blocked"));

                qApp->quit();
                QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

            } else {
                ui->card_pin->clear();
                _pin.clear();
                SessionManager s;
                PasswordWindow newps(_sessionManager, this);
                newps.show();
            }
        }
    } else {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Eneter your PIN!\n"), QMessageBox::Ok);
    }
}

void PasswordWindow::on_pushButton_clicked() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}
