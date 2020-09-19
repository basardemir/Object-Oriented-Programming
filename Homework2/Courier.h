/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 04/05/2020  */
#ifndef OOP2_COURIER_H
#define OOP2_COURIER_H
#include <string>
#include "Person.h"
#include <stdlib.h>

class Courier : public Person {
private:
    string vehicle;//Stores vehicle type
    int capacity;//Stores vehicle capacity
public:
    //Constructor
    Courier();//Default
    Courier(const string&, const string&);//Constructor with name,surname
    Courier(const string&,const string&,const string&);//Constructor with name,surname, vehicle
    Courier(const Courier &);//Copy Constructor

    string getVehicle() const;//Returns vehicle type
    int getCapacity() const;//Returns vehicle capacity

    bool operator==(const Courier &) const;//Operator == Overloading

    void print() const;//Prints content of courier
};

//Default Constructor
Courier::Courier() : Person() {
    this->vehicle = "";
    this->capacity = 0;
}

//Constructor with name,surname
Courier::Courier(const string& name, const string& surname) : Person(name, surname) {
    this->vehicle = "";
    this->capacity = 0;
}

//Constructor with name,surname, vehicle
Courier::Courier(const string& name, const string& surname,const string& vehicle) : Person(name, surname) {
    //Checks vehicle type is valid or invalid
    if (!(vehicle == "car" or vehicle == "motorcycle" or vehicle == "bicycle")) {
        cout << "Invalid vehicle type. Enter car, motorcycle or bicycle" << endl;//If it is invalid, gives error message
        exit(EXIT_FAILURE);
        return;
    } else { //If it is valid
        this->vehicle = vehicle; //Assign vehicle type
        //Capacity is determined by vehicle type
        if (vehicle == "bicycle")
            this->capacity = 10;
        if (vehicle == "motorcycle")
            this->capacity = 35;
        if (vehicle == "car")
            this->capacity = 200;
    }
}

//Operator == Overloading
bool Courier::operator==(const Courier &courier) const{//Checks equality
    bool flag = Person::operator==(courier);//Calls function of base class
    if (!flag) return false;
    return this->capacity == courier.capacity and this->vehicle == courier.vehicle;//Checks and return the boolean
}

//Copy Constructor
Courier::Courier(const Courier &courier) {
    //Copies everything from courier
    this->name = courier.name;
    this->surname = courier.surname;
    this->vehicle = courier.vehicle;
    this->capacity = courier.capacity;
}

//Returns vehicle type
string Courier::getVehicle()const {
    return this->vehicle;
}

//Returns vehicle capacity
int Courier::getCapacity()const {
    return this->capacity;
}

//Prints content of courier
void Courier::print() const{
    cout << this->getName() << " " << this->getSurname() << " " << this->getVehicle() << endl;
}

#include "Person.h"

#endif //OOP2_COURIER_H
