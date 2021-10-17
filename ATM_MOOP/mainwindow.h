#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "passwordwindow.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private
    slots:
    void digit_numbers();

    void on_digit_back_clicked();

    void on_digit_OK_clicked();

private:

    Ui::MainWindow *ui;
    PasswordWindow *passwindow;
};
#endif // MAINWINDOW_H
