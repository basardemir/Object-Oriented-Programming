/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 04/05/2020  */

#ifndef OOP2_PERSON_H
#define OOP2_PERSON_H

#include <string>
#include <iostream>

using namespace std;

class Person {
protected:
    string name;
    string surname;
public:
    //Constructors
    Person();//Default
    Person(const string&, const string&);//Constructor with name,surname
    Person(const Person &);//Copy Constructor

    //Getters
    string getName() const;//Returns name of person
    string getSurname() const;//Returns surname of person

    //Setters
    void setName(const string&);//Sets name from parameter
    void setSurname(const string&);//Sets surname from parameter

    //Operator Overloading
    bool operator==(const Person &) const;//Checks equality
};
//Default Constructor
Person::Person() {
    //Initializes
    this->name = "";
    this->surname = "";
}
//Constructor with name,surname
Person::Person(const string& name, const string& surname) {
    //Initializes with parameters
    this->name = name;
    this->surname = surname;
}
//Returns name of person
string Person::getName() const {
    return this->name;
}
//Sets name from parameter
void Person::setName(const string& name) {
    this->name = name;
}
//Returns surname of person
string Person::getSurname() const {
    return this->surname;
}
//Sets surname from parameter
void Person::setSurname(const string& surname) {
    this->surname = surname;
}
//Operator == Overload
bool Person::operator==(const Person &person) const{
    return this->name == person.name and this->surname == person.surname; //Checks equality
}
//Copy Constructor
Person::Person(const Person &person) {
    //It copies name and surname from object in parameter
    this->name = person.name;
    this->surname = person.surname;
}


#endif //OOP2_PERSON_H
