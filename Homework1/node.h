/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 08/04/2020  */
#ifndef OOP1_NODE_H

#include "pizza.h"

#define OOP1_NODE_H

// Pizza node class is used for storing pizzas and making
// connection between other pizzas in same order
class pizza_node {
private:
    Pizza *pizza;
    pizza_node *next;
public:
    //Constructor
    pizza_node(Pizza *pizza) {
        this->pizza = pizza;
        this->next = NULL;
    }

    //Deconstructor
    ~pizza_node() {
        delete this->pizza;
        next = NULL;
    }

    //Returns Pizza element of the class
    Pizza *getPizza() const;

    //Add new pizza node to next of the current node
    void addPizzaNode(pizza_node *);

    //Returns pointer of the next node
    pizza_node *nextNode() const;
};

//Returns Pizza element of the class
Pizza *pizza_node::getPizza() const {
    return this->pizza;
}

//Add new pizza node to next of the current node
pizza_node *pizza_node::nextNode() const {
    return this->next;
}

//Returns pointer of the next node
void pizza_node::addPizzaNode(pizza_node *node) {
    this->next = node;
}

// Drink node class is use for storing drinks and its amounts,
//it builds a connection between drinks in same order.
class drink_node {
private:
    string name; //Name of the drink
    int amount; //Drink amount
    drink_node *next;
public:
    //---------Constructor
    drink_node(string name, int amount) {
        this->name = name;
        this->amount = amount;
        this->next = NULL;
    }

    //---------Deconstructor
    ~drink_node() {
        next = NULL;
    }

    //---------Getters and Setters
    //Returns name of the drink
    string &getName();

    //Returns amount of the drink
    int getAmount() const;

    //Increment drink amount by one
    void addAmount();

    //Add new drink node to next of the current node
    void addDrinkNode(drink_node *);

    //Returns pointer of the next node
    drink_node *nextNode() const;
};

//Returns name of the drink
string &drink_node::getName() {
    return this->name;
}

//Returns amount of the drink
int drink_node::getAmount() const {
    return this->amount;
}

//Increment drink amount by one
void drink_node::addAmount() {
    this->amount = this->amount + 1;
}

//Add new drink node to next of the current node
void drink_node::addDrinkNode(drink_node *drink) {
    this->next = drink;
}

//Returns pointer of the next node
drink_node *drink_node::nextNode() const {
    return this->next;
}

#endif //OOP1_NODE_H