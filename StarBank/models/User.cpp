#include "User.h"

User::User(size_t id, string firstName,  string lastName, string middleName): _id(id), _firstName(firstName), _lastName(lastName), _middleName(middleName){

}

User:: ~User(){

}


size_t& User::id(){
    return _id;
}
string& User::firstName(){
    return _firstName;
}
string& User::lastName(){
    return _lastName;
}
string& User::middleName(){
    return _middleName;
}


const size_t& User::id() const{
    return _id;
}
const string& User::firstName() const{
    return _firstName;
}
const string& User::lastName() const{
    return _lastName;
}

const string& User::middleName() const{
    return _middleName;
}

ostream& operator<<(ostream& os, const User& user){
    os << "ID: " << user.id() << " " << user.firstName() << " " << user.lastName() << " " << user.middleName() << endl;
    return os;
}