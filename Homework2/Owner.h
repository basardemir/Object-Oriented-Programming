/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 04/05/2020  */

#ifndef OOP2_OWNER_H
#define OOP2_OWNER_H
#include "Person.h"

class Owner : public Person {
private:
    double ownership;
public:
    //Constructors
    Owner();//Default
    Owner(const string&, const string&);//Constructor with name,surname
    Owner(const string&, const string&, const int);//Constructor with name,surname, ownership percentage
    Owner(const Owner &);//Copy Constructor

    double getOwnership() const;//Returns ownership percentage

    void setOwnership(const double);//Sets ownership percentage

    bool operator==(const Owner &) const;//Operator == Overloading

    void print() const;//Prints content of owner
};

//Default Constructor
Owner::Owner() : Person() {
    this->ownership = 0;
}

//Constructor with name,surname, ownership percentage
Owner::Owner(const string& name, const string& surname, const int ownership) : Person(name, surname) {
    this->ownership = ownership;
}

//Constructor with name,surname
Owner::Owner(const string& name, const string& surname) : Person(name, surname) {
    this->ownership = 0;
}

//Returns ownership percentage
double Owner::getOwnership() const {
    return this->ownership;
}

//Sets ownership percentage
void Owner::setOwnership(const double percentage) {
    this->ownership = percentage;
}

//Operator == Overloading
bool Owner::operator==(const Owner &owner)const { //Checks equality
    if (!Person::operator==(owner)) { //Calls function of base class
        return false;
    }
    return owner.ownership == this->ownership; //Checks and return the boolean
}

//Copy Constructor
Owner::Owner(const Owner &owner) {
    //Copies everything from owner
    this->name = owner.name;
    this->surname = owner.surname;
    this->ownership = owner.ownership;
}

//Prints content of owner
void Owner::print() const{
    cout << this->getName() << " " << this->getSurname() << " " << this->getOwnership() << endl;
}

#include "Person.h"

#endif //OOP2_OWNER_H
