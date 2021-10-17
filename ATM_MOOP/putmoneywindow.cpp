#include "putmoneywindow.h"
#include "ui_putmoneywindow.h"
#include <QProcess>
#include "passwordwindow.h"

PutMoneyWindow::PutMoneyWindow(SessionManager sm, QWidget *parent) :
        _sessionManager(sm),
        QDialog(parent),
        ui(new Ui::PutMoneyWindow) {
    ui->setupUi(this);
    ui->user->setText(sm.getUser());
    ui->pushButton->setEnabled(false);
    ui->banknotes_2->setReadOnly(true);

}

PutMoneyWindow::~PutMoneyWindow() {
    delete ui;
}

void PutMoneyWindow::on_pushButton_3_clicked() {
    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(true);
    _sessionManager.putMoney(50);
    QString n;

    n = ui->banknotes_2->toPlainText() + "50\n";

    ui->banknotes_2->setText(n);
    _sum += 50;
    ui->sum->setText(QString::number(_sum));
}

void PutMoneyWindow::on_pushButton_4_clicked() {
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);

    _sessionManager.putMoney(100);
    QString n;

    n = ui->banknotes_2->toPlainText() + "100\n";

    ui->banknotes_2->setText(n);
    _sum += 100;
    ui->sum->setText(QString::number(_sum));
}

void PutMoneyWindow::on_pushButton_5_clicked() {
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    _sessionManager.putMoney(200);
    QString n;

    n = ui->banknotes_2->toPlainText() + "200\n";

    ui->banknotes_2->setText(n);
    _sum += 200;
    ui->sum->setText(QString::number(_sum));
}

void PutMoneyWindow::on_pushButton_6_clicked() {
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    _sessionManager.putMoney(500);
    QString n;

    n = ui->banknotes_2->toPlainText() + "500\n";

    ui->banknotes_2->setText(n);
    _sum += 500;
    ui->sum->setText(QString::number(_sum));

}

void PutMoneyWindow::on_pushButton_clicked() {
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(false);
    QMessageBox msgBox;
    QString a = QString::number(_sum) + "$ incashed successfuly!\n";
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

void PutMoneyWindow::on_pushButton_2_clicked() {
    this->close();
}
