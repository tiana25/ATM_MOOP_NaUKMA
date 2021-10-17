#include "setlimitwindow.h"
#include "ui_setlimitwindow.h"
#include "passwordwindow.h"
#include <QProcess>

SetLimitWindow::SetLimitWindow(SessionManager sm, QWidget *parent) :
        _sessionManager(sm),
        QDialog(parent),
        ui(new Ui::SetLimitWindow) {
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

SetLimitWindow::~SetLimitWindow() {
    delete ui;
}

void SetLimitWindow::digit_numbers() {
    QPushButton *digit = (QPushButton *) sender();

    QString s;

    s = ui->amount->text() + digit->text();

    ui->amount->setText(s);
}

void SetLimitWindow::on_digit_OK_clicked() {
    QString s = ui->amount->text();
    if (!s.isEmpty()) {
        _sessionManager.setLimit(s.toInt());

        QMessageBox msgBox(this);
        QString a = "Your new limit is:\n";
        a += QString::number(_sessionManager.getLimit());
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
    } else {
        QMessageBox::warning(this, QObject::tr("Error"),
                             QObject::tr("Enter new limit!\n"), QMessageBox::Ok);
    }
}

void SetLimitWindow::on_digit_back_clicked() {
    QString s;
    s = ui->amount->text();
    s.resize(s.size() - 1);

    ui->amount->setText(s);
}

void SetLimitWindow::on_returnFromSetLimit_clicked() {
    this->close();
}
