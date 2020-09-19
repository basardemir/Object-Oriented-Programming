/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 08/04/2020  */
#ifndef OOP1_ORDER_H
#define OOP1_ORDER_H

#include "node.h"

//Order class is used for storing data of order.
//customer name, drinks, pizzas, price of order
class Order {
private:
    string customer; //Name of the customer
    pizza_node *pizza_head; //Pizza linked list which keeps all pizza orders
    drink_node *drink_head; //Drink linked list which keeps all drink orders
    double price; //Keeps price of the order
    Order *next;
public:
    //---------Constructors
    Order(string &, pizza_node *, drink_node *); //For orders which contains drink

    Order(string &, pizza_node *);//For orders which does not contain drink

    //---------Deconstructor
    ~Order();

    //---------General Order Functions
    //Returns price of order
    double getPrice() const;

    //Calculates price of order
    void calculatePrice();

    //Prints order in proper form
    void printOrder() const;

    //---------Getters and setters
    //Returns next Order
    Order *nextOrder() const;

    //Adds new Order
    void addOrder(Order *);

    //Returns customer name
    string getName() const;
};

//Constructs order class and calculates its price with drink
Order::Order(string &name, pizza_node *pizza, drink_node *drink) {
    this->customer = name;
    this->pizza_head = pizza;
    this->drink_head = drink;
    this->price = 0;
    this->next = NULL;
    this->calculatePrice();
}

//Constructs order class and calculates its price without drink
Order::Order(string &name, pizza_node *pizza) {
    this->customer = name;
    this->pizza_head = pizza;
    this->price = 0;
    this->drink_head = NULL;
    this->next = NULL;
    calculatePrice();
}

//Returns price of order
double Order::getPrice() const {
    return this->price;
}

//Calculates price of order
void Order::calculatePrice() {
    pizza_node *ptr = pizza_head;

    //Calculates prices of pizzas with iteration over the pizza head
    while (ptr) {
        this->price += ptr->getPizza()->getPrice();
        ptr = ptr->nextNode();
    }

    //Calculates prices of drinks with iteration over the drink head
    //Prices are given in description
    drink_node *traverse = drink_head;
    //Checks availability of drink head
    while (traverse != NULL) {
        if (traverse->getName() == "cola") {
            this->price += 4 * traverse->getAmount();
        }
        if (traverse->getName() == "soda") {
            this->price += 2 * traverse->getAmount();
        }
        if (traverse->getName() == "ice tea") {
            this->price += 3 * traverse->getAmount();
        }
        if (traverse->getName() == "fruit juice") {
            this->price += 3.5 * traverse->getAmount();
        }
        traverse = traverse->nextNode();
    }
}

//Prints order in proper form
void Order::printOrder() const {
    cout << "-------------" << endl;
    //Prints name of the customer
    cout << "Name: " << this->customer << endl << endl;

    //Iterates over pizzas and prints their properties
    pizza_node *ptr = pizza_head;
    while (ptr) {
        cout << ptr->getPizza()->getName() << ": ";
        ptr->getPizza()->printIngredients();
        cout << endl;
        cout << "size: " << ptr->getPizza()->getSize() << ", crust: " << ptr->getPizza()->getCrust() << endl << endl;
        ptr = ptr->nextNode();
    }

    //Iterates over drinks and prints their names and amounts
    drink_node *traverse = drink_head;
    while (traverse) {
        if (traverse->nextNode() == NULL) {
            cout << traverse->getAmount() << " " << traverse->getName();
        } else {
            cout << traverse->getAmount() << " " << traverse->getName() << ", ";
        }

        traverse = traverse->nextNode();
    }
    //Checks drinks nullability then, decides for break line
    if (drink_head != NULL)
        cout << endl;
    cout << "-------------" << endl;
}

//Deconstructor
Order::~Order() {
    //Iterates over pizzas and deletes them
    pizza_node *ptr = pizza_head;
    while (ptr) {
        pizza_node *temp = ptr;
        ptr = ptr->nextNode();
        delete temp;
    }
    delete ptr;

    //Iterates over drinks and deletes them
    drink_node *traverse = drink_head;
    while (traverse) {
        drink_node *tmp = traverse;
        traverse = traverse->nextNode();
        delete tmp;
    }
    delete traverse;
    next = NULL;
}

Order *Order::nextOrder() const{
    return this->next;
}

void Order::addOrder(Order *ptr) {
    this->next = ptr;
}

string Order::getName() const {
    return this->customer;
}

#endif //OOP1_ORDER_H