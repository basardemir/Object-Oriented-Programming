/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 04/05/2020  */

#ifndef OOP2_BUSINESS_H
#define OOP2_BUSINESS_H

#include "Person.h"
#include "LinkedList.h"
#include "Courier.h"
#include "Owner.h"
#include <stdlib.h>

class Business {
private:
    string name; //Stores name of the business
    string address;//Stores address of the business
    const Owners *owners;//Stores owners of the business
    Couriers *couriers;//Stores owners of the business
    int owner_num;//Stores number of the owners
public:
    //Constructors
    Business(); //Default
    Business(const string&, const string&, const Owner* const , const int) ;//Constructor with name,address, owners, number of owners
    Business(const Business&);//Bussiness Copy Constructor
    //Setters
    void setAddress(const string&);//Sets address from parameter
    void setName(const string&);//Sets name from parameter

    //Getters
    string getAddress() const;//Returns address of business
    string getName() const;//Returns name of business

    //Specialized Functions
    void hire_courier(const Courier &);//Deletes specific courier
    void fire_courier(Courier &);//Adds new courier
    int calculate_shipment_capacity() const;//Returns total capacity

    //List Functions
    void list_couriers() const;//Prints all couriers
    void list_owners() const;//Prints all owners

    //Operator overloading
    void operator()() const; //Prints all content of business
    Courier operator[](int) const;//Returns courier that is in given index

    //Deconstructor
    ~Business();
};
//Default Constructor
Business::Business() {
    //Initialize business object
    this->owners = new Owners();
    this->couriers = new Couriers();
    this->name = "";
    this->address = "";
    this->owner_num = 0;
}
//Constructor with name,address, owners, number of owners
Business::Business(const string& name, const string& address, const Owner* const owner_array, const int number_of_owners) {
    //Initialize
    this->name = name;
    this->address = address;
    Owners* owners = new Owners();
    this->couriers = new Couriers();
    //Read from owner array
    for (int i = 0; i < number_of_owners; i++) {
        Owner ptr = owner_array[i]; //Takes owner that is index i
        ptr.setOwnership(100.0 / number_of_owners); //Sets ownership of owner
        Owner *own = new Owner(ptr); //Creates new owner from array[i]
        owners->addOwner(own); //Adds new owner to owners list
    }
    if (number_of_owners == 0) {//Gives error message if there is no owner
        cout << "Business must have owner." << endl;
    }
    this->owners=owners;
    this->owner_num = number_of_owners;//Assign number of owners to business
}
//Copy Constructor of Business Class
Business::Business(const Business & business) {
    //Copies everything from business object
    this->name = business.name;
    this->address = business.address;
    this->owner_num=business.owner_num;
    Owners* owner_list = new Owners(*(business.owners)); //Creates new Owner list by copying items
    this->owners=owner_list;
    Couriers* courier_list = new Couriers(*(business.couriers));//Creates new couriers list by copying items
    this->couriers=courier_list;
}
//Adds new cousrier
void Business::hire_courier(const Courier &courier) {
    Courier *cr = new Courier(courier); //Creates courier from parameter
    couriers->addCourier(cr); //Adds new courier to courier list
}

//Deletes specific courier
void Business::fire_courier(Courier &courier) {
    couriers->deleteCourier(&courier);
}
//Prints all couriers
void Business::list_couriers()const {
    couriers->list();
}
//Prints all owners
void Business::list_owners()const {
    owners->list();
}
//Returns total capacity
int Business::calculate_shipment_capacity()const {
    return this->couriers->getTotalCapacity();
}
//Prints all content of business
void Business::operator()()const {
    cout << this->getName() << " " << this->getAddress() << endl; //Print name and address of business
    list_owners(); //Prints all owners
    list_couriers();//Prints all couriers
}
//Returns address of business
string Business::getAddress()const {
    return this->address;
}
//Returns name of business
string Business::getName() const{
    return this->name;
}
//Sets address from parameter
void Business::setAddress(const string& address) {
    this->address = address;
}
//Sets name from parameter
void Business::setName(const string& name) {
    this->name = name;
}
//Returns courier that is in given index
Courier Business::operator[](int i)const {
    if (i > this->couriers->getSize() - 1 or i < 0) {//Checks range
        cout << "Enter valid index. Program will be terminated."<< endl;//Gives error message
        exit(EXIT_FAILURE); //Exits code
    } else {
        return *(couriers->getByIndex(i)->getCourier());//Returns intended courier
    }
}
//Deconstructor
Business::~Business() {
    delete this->owners; //Delete owner list
    delete this->couriers;//Delete courier list
}





#endif //OOP2_BUSINESS_H
