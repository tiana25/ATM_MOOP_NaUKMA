#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AccountsService.h"
#include <SessionManager.h>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
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

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digit_numbers() {
    QPushButton *digit = (QPushButton *) sender();

    QString _cardNum;

    _cardNum = ui->card_number->text() + digit->text();

    ui->card_number->setText(_cardNum);
}

void MainWindow::on_digit_back_clicked() {
    QString _cardNum;
    _cardNum = ui->card_number->text();
    _cardNum.resize(_cardNum.size() - 1);

    ui->card_number->setText(_cardNum);
}

void MainWindow::on_digit_OK_clicked() {

    if (!ui->card_number->text().isEmpty()) {
        validateCard(ui->card_number->text());

        SessionManager s;

        s.checkCard(ui->card_number->text());

        if (s.cardNumIsOk()) {
            hide();
            passwindow = new PasswordWindow(s, this);
            passwindow->show();
        }
    } else {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter your PIN!\n"), QMessageBox::Ok);
    }
}





