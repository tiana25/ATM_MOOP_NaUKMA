#include "transactionhistorywindow.h"
#include "ui_transactionhistorywindow.h"
#include <QSqlQueryModel>

TransactionHistoryWindow::TransactionHistoryWindow(SessionManager sm, QWidget *parent) :
        _sessionManager(sm),
        QDialog(parent),
        ui(new Ui::TransactionHistoryWindow) {
    ui->setupUi(this);
    ui->user->setText(sm.getUser());
}

TransactionHistoryWindow::~TransactionHistoryWindow() {
    delete ui;
}

void TransactionHistoryWindow::on_pushButton_6_clicked() {
    this->close();
}

void TransactionHistoryWindow::on_pushButton_clicked() {
    QSqlQueryModel *modal = new QSqlQueryModel();


    DBPath path;
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path.getPath());
    db.open();

    QSqlQuery *query = new QSqlQuery(db);
    query->prepare(
            "SELECT * FROM TRANSACTION_ATM WHERE source_account_number = " + _sessionManager.getActiveCardNumber() +
            " OR destination_account_number = " + _sessionManager.getActiveCardNumber());
    query->exec();
    modal->setQuery(*query);
    ui->tableView->setModel(modal);
    db.close();
}


