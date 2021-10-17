#pragma once

#include <QString>
#include <map>

class User {

private:
    int _id;
    QString _firstName;
    QString _lastName;
    QString _middleName;

public:
    User() {}

    User(int id, QString firstName, QString lastName, QString middleName);

    ~User();

    User &operator=(const User &u) {
        _id = u.id();
        _middleName = u.middleName();
        _firstName = u.firstName();
        _lastName = u.lastName();
        return *this;
    }

    int &id();

    QString &firstName();

    QString &lastName();

    QString &middleName();


    const int &id() const;

    const QString &firstName() const;

    const QString &lastName() const;

    const QString &middleName() const;
};
