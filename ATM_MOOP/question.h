#ifndef QUESTION_H
#define QUESTION_H
#pragma once

#include <QDialog>
//#include "passwordwindow.h"
namespace Ui {
    class Question;
}

class Question : public QDialog {
    Q_OBJECT

public:
    explicit Question(QWidget *parent = nullptr);

    ~Question();

private
    slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Question *ui;
};

#endif // QUESTION_H
