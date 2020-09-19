/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 04/05/2020  */
#ifndef OOP2_LINKEDLIST_H
#define OOP2_LINKEDLIST_H

#include "Person.h"
#include "Courier.h"
#include "Owner.h"

class CourierNode {
private:
    Courier *courier;//Courier object pointer
    CourierNode *next;
public:
    //Constructors
    CourierNode(); //Default
    CourierNode(Courier *); //Constructor with Courier parameter

    //Getters
    Courier *getCourier() const ; //Returns pointer of Courier
    CourierNode *getNext() const ;//Returns pointer of next node

    //Setters
    void setCourier(Courier *); //Set courier from parameter
    void setNext(CourierNode *); //Set next node from parameter

    //Deconstructor
    ~CourierNode();
};

//Default Constructor
CourierNode::CourierNode() {
    //Initialize everything as NULL
    this->courier = NULL;
    this->next = NULL;
}

//Constructor with Courier parameter
CourierNode::CourierNode(Courier *courier) {
    //Set courier from parameter
    this->courier = courier;
    this->next = NULL;
}

//Returns pointer of Courier
Courier *CourierNode::getCourier()const{
    return this->courier;
}

//Set courier from parameter
void CourierNode::setCourier(Courier *courier) {
    Courier *cr = this->courier; //Keeps current courier
    this->courier = courier; //Set courier from parameter
    if (cr == NULL)
        return; //If old one is NULL, return
    delete cr; //If old one is not NULL, delete it
}

//Returns pointer of next node
CourierNode *CourierNode::getNext()const {
    return this->next;
}

//Set next node from parameter
void CourierNode::setNext(CourierNode *node) {
    this->next = node;
}

//Deconstructor
CourierNode::~CourierNode() {
    delete this->courier;
}

//Class for keeping all couriers in LinkedList
class Couriers {
private:
    int numCourier; //Counts courier number in the LinkedList
    CourierNode *head; //Keeps head of LinkedList
public:
    //Constructor
    Couriers();//Default Constructor
    Couriers(const Couriers&);//Copy Constructor

    //Getters
    const int getSize() const; //Returns courier number of list
    CourierNode *getByIndex(const int); //Returns courier node that is in given index
    const int getTotalCapacity() const; //Calculates total capacity of couriers

    //Specified Functions
    void addCourier(Courier *); //Adds new courier to list
    void deleteCourier(const Courier *); //Deletes courier from list
    void deleteByIndex(const int); //Deletes courier which is in given index
    void list() const; //Lists all couriers in the list

    //Deconstructor
    ~Couriers();
};

//Default Constructor
Couriers::Couriers() {
    //Initialize variables
    this->head = NULL;
    this->numCourier = 0;
}
//Returns courier number of list
const int Couriers::getSize() const {
    return this->numCourier;
}
//Adds new courier to list
void Couriers::addCourier(Courier *courier) {
    CourierNode *ptr = head;
    if (head == NULL) { //Checks for empty lists
        this->head = new CourierNode(courier); //It adds as a head
    } else { //Not empty case
        while (ptr->getNext() != NULL) {
            ptr = ptr->getNext(); //Iterates over list and comes to last element
        }
        ptr->setNext(new CourierNode(courier)); //Add new courier to end of the list
    }
    this->numCourier++; //Increment courier number
}
//Deletes courier from list
void Couriers::deleteCourier(const Courier *courier) {
    CourierNode *ptr = head;
    if (this->numCourier == 0) { //If list is empty, it gives error message
        cout << "There is no courier" << endl;
        return;
    }
    if (*(head->getCourier()) == *(courier)) { //If courier is located at head
        head = head->getNext();//Shifts the head
        delete ptr; //Deletes courier node
    } else {
        //It iterates over the list and tries to find a node which is one node before the courier
        while (ptr->getNext() != NULL and !(*(ptr->getNext()->getCourier()) == *(courier))) {
            ptr = ptr->getNext();
        }
        if (ptr->getNext() == NULL and ptr->getCourier() != courier) { //If pointer comes to last element
            cout << "Courier Not Found" << endl; //Gives error message
            return;
        } else {
            CourierNode *temp = ptr->getNext(); //Temp keeps courier node that will be deleted
            ptr->setNext(ptr->getNext()->getNext()); //List connections are set
            delete temp; //Deletes courier node
        }
    }
    this->numCourier--; //Decrement number of couriers
}
//Returns courier node that is in given index
CourierNode *Couriers::getByIndex(const int index) {
    if (index >= this->numCourier or index < 0) { //Range checking
        cout << "Index out of range" << endl;  //Gives error message
        return NULL;
    } else {
        int counter = 0; //Keeps current index
        CourierNode *ptr = head;
        while (counter != index) {//Iterates until it comes to intended index
            ptr = ptr->getNext();
            counter++;
        }
        return ptr; //Returns node which is in given index
    }
}
//Deletes courier which is in given index
void Couriers::deleteByIndex(const int index) {
    if (index >= this->numCourier or index < 0) {//Range checking
        cout << "Index out of range" << endl; //Gives error message
        return;
    } else {
        CourierNode *ptr = this->head;
        if (index == 0) {//If courier is located at head
            head = head->getNext();//Shifts the head
            delete ptr; //Deletes courier node
        } else {
            int counter = 0; //Keeps current index
            while (counter + 1 != index) {//Iterates until it comes to intended index-1
                ptr = ptr->getNext();
                counter++;
            }
            CourierNode *temp = ptr->getNext(); //Temp keeps courier node that will be deleted
            ptr->setNext(ptr->getNext()->getNext());//List connections are set
            delete temp;//Deletes courier node
        }
        this->numCourier--; //Decrement number of couriers
    }
}
//Lists all couriers in the list
void Couriers::list()const {
    if (this->head == NULL) { //If head is empty, it gives error message
        cout << "There is no courier to list." << endl;
    } else {
        CourierNode *ptr = head;
        while (ptr != NULL) { //It iterates over the list
            Courier *courier = ptr->getCourier(); //Takes the courier from node
            courier->print(); //It prints contents of courier
            ptr = ptr->getNext(); //It updates pointer
        }
    }
}
//Decontructor
Couriers::~Couriers() {
    CourierNode *ptr = head;
    while (ptr != NULL) { //It iterates over the list
        CourierNode *temp = ptr; //Temp keeps courier node that will be deleted
        ptr = ptr->getNext(); //It updates pointer
        delete temp;//Deletes node
    }
}
//Calculates total capacity of couriers
const int Couriers::getTotalCapacity()const {
    if (head == NULL) { //If list is empty, it returns 0
        return 0;
    } else {
        int total = 0;//Keeps current capacity
        CourierNode *ptr = head;//It iterates over the list
        while (ptr != NULL) {
            total += ptr->getCourier()->getCapacity(); //Increment capacity by courier capacity
            ptr = ptr->getNext();//It updates pointer
        }
        return total;//Returns total capacity
    }
}

//Copy Constructor of Couriers
Couriers::Couriers(const Couriers& courier)  {
    this->head=NULL;
    this->numCourier=courier.numCourier;
    CourierNode* ptr = courier.head;
    while(ptr!=NULL){
        Courier a = *(ptr->getCourier());
        Courier* c = new Courier(a.getName(),a.getSurname(),a.getVehicle());
        this->addCourier(c);
        ptr=ptr->getNext();
    }
}

class OwnerNode {
private:
    Owner *owner; //Owner object pointer
    OwnerNode *next;
public:
    //Constructors
    OwnerNode(); //Default
    OwnerNode(Owner *);//Constructor with Owner parameter

    //Getters
    Owner *getOwner() const;//Returns Owner object of the node
    OwnerNode *getNext() const;//Returns next of node

    //Setters
    void setOwner(Owner *); //Sets owner from parameter
    void setNext(OwnerNode *);//Sets next of node from parameter

    //Deconstructor
    ~OwnerNode();
};
//Default Constructor
OwnerNode::OwnerNode() {
    //Initialize
    this->owner = NULL;
    this->next = NULL;
}
//Constructor with Owner parameter
OwnerNode::OwnerNode(Owner *owner) {
    //Initialize with given owner
    this->owner = owner;
    this->next = NULL;
}
//Returns Owner object of the node
Owner *OwnerNode::getOwner()const {
    return this->owner;
}
//Sets owner from parameter
void OwnerNode::setOwner(Owner *owner) {
    Owner *ptr = this->owner; //Keeps current owner object
    this->owner = owner; //Set owner
    if(ptr==NULL) //If old one is NULL, it returns
        return;
    delete ptr; //Delete old owner object
}
//Returns next of node
OwnerNode *OwnerNode::getNext() const {
    return this->next;
}
//Sets next of node from parameter
void OwnerNode::setNext(OwnerNode *node) {
    this->next = node;
}
//Deconstructor
OwnerNode::~OwnerNode() {
    delete this->owner;
}

class Owners {
private:
    int owner_number;
    OwnerNode *head;
public:
    Owners(); //Default Constructor
    Owners(const Owners&);//Copy Constructor

    void addOwner(Owner *); //Add new owner to list

    void list()const;//Prints contents of list

    ~Owners(); //Deconstructor
};

//Default Constructor
Owners::Owners() {
    //Initializes
    this->head = NULL;
    this->owner_number = 0;
}
//Add new owner to list
void Owners::addOwner(Owner *owner) {
    if (this->head == NULL) { //Checks for empty lists
        head = new OwnerNode(owner);//It adds as a head
    } else {
        OwnerNode *ptr = head;
        while (ptr->getNext() != NULL) {
            ptr = ptr->getNext();//Iterates over list and comes to last element
        }
        ptr->setNext(new OwnerNode(owner));//Add new owner node to end of the list
    }
    this->owner_number++;//Increment owner number
}
//Prints contents of list
void Owners::list() const{
    OwnerNode *ptr = head;
    if (head == NULL) {//If head is empty, it gives error message
        cout << "There is no owner to list" << endl;
    } else {
        while (ptr != NULL) {//It iterates over the list
            Owner *owner = ptr->getOwner(); //Takes the owner from node
            owner->print();//It prints contents of owner
            ptr = ptr->getNext();//It updates pointer
        }
    }
}
//Deconstructor
Owners::~Owners() {
    OwnerNode *ptr = head;
    while (ptr != NULL) {//It iterates over the list
        OwnerNode *temp = ptr; //Temp keeps owner node that will be deleted
        ptr = ptr->getNext();//It updates pointer
        delete temp;//Deletes node
    }
}

//Copy Constructor of Owners LinkedList
Owners::Owners(const Owners& owner) {
    this->head=NULL;
    this->owner_number= owner.owner_number;
    OwnerNode* ptr = owner.head;
    while(ptr!=NULL){
        Owner a = *(ptr->getOwner());
        Owner* o = new Owner(a.getName(),a.getSurname(),a.getOwnership());
        this->addOwner(o);
        ptr=ptr->getNext();
    }
}

#endif //OOP2_LINKEDLIST_H
