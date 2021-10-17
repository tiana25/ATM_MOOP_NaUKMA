
#include <string>
#include <iostream>
using namespace std;
#include <map>
#ifndef STARBANKATM_MOOP_KMA_USER_H
#define STARBANKATM_MOOP_KMA_USER_H

class User {

private:
    size_t _id;
    string _firstName;
    string _lastName;
    string _middleName;

public:
    User(){}
    User(size_t id, string firstName,  string lastName, string middleName);
    ~User();
    User& operator=(const User& u){
        _id = u.id();
        _middleName = u.middleName();
        _firstName = u.firstName();
        _lastName = u.lastName();
        return *this;
    }

    size_t& id();
    string& firstName();
    string& lastName();
    string& middleName();


    const size_t& id() const;
    const string& firstName() const;
    const string& lastName() const;
    const string& middleName() const;
};
ostream& operator<<(ostream&, const User&);

#endif