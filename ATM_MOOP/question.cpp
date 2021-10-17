#include "question.h"
#include "ui_question.h"
#include <QProcess>
#include <QMessageBox>

Question::Question(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Question) {
    ui->setupUi(this);
}

Question::~Question() {
    delete ui;
}

void Question::on_pushButton_clicked() {
    QMessageBox msgBox;
    QString a = "Thank you for using our ATM!";
    msgBox.setText(a);
    msgBox.exec();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}

void Question::on_pushButton_2_clicked() {
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
