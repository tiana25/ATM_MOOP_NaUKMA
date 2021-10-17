#include "ATMdata/ATMHeaders/User.h"

User::User(int id, QString firstName, QString lastName, QString middleName) : _id(id), _firstName(firstName),
                                                                              _lastName(lastName),
                                                                              _middleName(middleName) {

}

User::~User() {

}

int &User::id() {
    return _id;
}

QString &User::firstName() {
    return _firstName;
}

QString &User::lastName() {
    return _lastName;
}

QString &User::middleName() {
    return _middleName;
}


const int &User::id() const {
    return _id;
}

const QString &User::firstName() const {
    return _firstName;
}

const QString &User::lastName() const {
    return _lastName;
}

const QString &User::middleName() const {
    return _middleName;
}

