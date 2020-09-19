/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 08/04/2020  */
#ifndef OOP1_PIZZA_H

#define OOP1_PIZZA_H

#include <cmath>
#include <iostream>
#include "strnode.h"

//Pizza class is used for storing data of pizzas
class Pizza {
private:
    string name; //Keeps pizza name
    string size; //Keeps pizza size
    strNode *ingredients; //Keeps ingredients of the pizza
    string crust_type; //Keeps crust type
public:
    //---------Constructors
    Pizza();//Default constructor

    Pizza(string &size, string &crust_type, int pizza_type); //Pizza constructor for given inputs

    //---------Copy Constructor
    Pizza(const Pizza &);

    //---------Deconstructor
    ~Pizza();

    //---------Functions for private values
    //Returns size of the pizza
    string getSize() const;

    //Returns price of the pizza
    int getPrice() const;

    //Returns name of the pizza
    string getName() const;

    //Returns crust type of the pizza
    string getCrust() const;

    //---------Functions for ingredient operations
    //Function for asking undesirable ingredients
    void removeIngredient();

    //Function adds ingredient to the pizza
    void addIngredients(string);

    //Prints ingredients in proper forms
    void printIngredients()const;

    //Removes ingredient from the pizza
    void remove(const string &);
};

//---------Functions for string-integer operations
//Checks inside of the string and determines is it integer or not
bool isInteger(string);

//The function converts strings to positive integer type
int string_to_integer(string);

//Default constructor
Pizza::Pizza() {
    this->size = "medium";
    this->crust_type = "normal";
    this->ingredients = NULL;
    this->addIngredients("mozarella");
}

//Constructor respect to user inputs
Pizza::Pizza(string &size, string &crust_type, int pizza_type) {
    this->size = size;
    this->crust_type = crust_type;
    this->ingredients = NULL;
    switch (pizza_type) { //Adds ingredients according to pizza type
        case 1: //Adding ingredients of Chicken Pizza
            this->name = "Chicken Pizza";
            this->addIngredients("mozarella");
            this->addIngredients("chicken");
            this->addIngredients("mushroom");
            this->addIngredients("corn");
            this->addIngredients("onion");
            this->addIngredients("tomato");
            break;
        case 2: //Adding ingredients of Broccoli Pizza
            this->name = "Broccoli Pizza";
            this->addIngredients("mozarella");
            this->addIngredients("broccoli");
            this->addIngredients("pepperoni");
            this->addIngredients("olive");
            this->addIngredients("corn");
            this->addIngredients("onion");
            break;
        case 3: //Adding ingredients of Sausage Pizza
            this->name = "Sausage Pizza";
            this->addIngredients("mozarella");
            this->addIngredients("sausage");
            this->addIngredients("tomato");
            this->addIngredients("olive");
            this->addIngredients("mushroom");
            this->addIngredients("corn");
            break;
    }
}

//Copy constructor
Pizza::Pizza(const Pizza &_pizza) {
    //Copies properties that are in string form
    this->name = string(_pizza.name);
    this->size = string(_pizza.size);
    this->crust_type = string(_pizza.crust_type);

    //Copies ingredients
    this->ingredients = NULL;
    strNode *ptr = _pizza.ingredients;
    //Iterates over ingredients and adds them into ingredients of new pizza
    while (ptr) {
        this->addIngredients(ptr->getString()); //Adds ingredients
        ptr = ptr->nextNode();
    }

}

//Function for asking undesirable ingredients
void Pizza::removeIngredient() {
    cout << "Please enter the number of ingredient you want to remove from your pizza." << endl;
    int i = 0;
    int full_size = 0;
    //For storing indexes of ingredients
    string *ingredient_arr = new string[10];
    strNode *ptr = this->ingredients;
    //Iterates over ingredients and prints them
    while (ptr) {
        cout << i + 1 << ". "; //Prints indexes
        cout << ptr->getString(); //Prints ingredient names
        cout << endl;
        ingredient_arr[i + 1] = ptr->getString(); //Fills index array
        ptr = ptr->nextNode();
        full_size++; //Updating size
        i++;
    }
    int current_size = full_size;
    cout << "Press 0 to save it." << endl;

    string in; //Keeps user's input

    bool *visited = new bool[7]; //To check repeated inputs
    for (int j = 0; j < 7; j++)
        visited[j] = false;  //Fills array with false values

    //Checks for unsuitable inputs
    while (true) {
        getline(cin, in); //Takes user input
        cin.clear(); //Clears buffer
        if(in.empty()) {
            cout << "Input is at out of range or not valid" << endl;
            cout<<"Please enter proper input:"<<endl;
            continue;
        }
        bool check = isInteger(in); //Checks user input
        if (check) {
            int input = string_to_integer(in); //Converts string to integer
            if (input == 0) {
                break; //For input 0 it breaks the while and saves
            } else if (input > full_size or input < 0) { //Controls range of the input
                cout << "Input is at out of range" << endl; //Prints error message
                cout<<"Please enter proper input:"<<endl;
            } else {
                if (!visited[input]) { //Checks the is input comes first time
                    //Removes it with the help of array
                    remove(ingredient_arr[input]);
                    //Marks as visited
                    visited[input] = true;
                    current_size--;
                    if(current_size==1){ //It checks one ingredient condition
                        cout<<"There is only one ingredient. You cannot remove anymore."<<endl;
                        cout<<"Your preferences are saved."<<endl;
                        break; //It prevents constructing empty pizza
                    }
                }
                else{
                    cout<<"You have already deleted this ingredient."<<endl;
                    cout<<"Please enter another input:"<<endl;
                }
            }
        } else {
            cout << "Input is at out of range or not valid" << endl;
            cout<<"Please enter proper input:"<<endl;
        }
    }
    //For empty pizzas, it adds alert message
    if (current_size == 0) {
        this->addIngredients("There are no ingredients in it.");
    }
    //Deletes allocated arrays
    delete[] visited;
    delete[] ingredient_arr;
}

//Returns size of pizza
string Pizza::getSize()const {
    return this->size;
}

//Calculates price respect to its size
int Pizza::getPrice()const {
    if (this->size == "small") {
        return 15;
    }
    if (this->size == "medium") {
        return 20;
    }
    if (this->size == "big") {
        return 25;
    }
    return 0;
}

//Returns name of pizza
string Pizza::getName()const {
    return this->name;
}

//Returns crust type of pizza
string Pizza::getCrust()const {
    return this->crust_type;
}

//Function adds ingredient to the pizza
void Pizza::addIngredients(string ingredient) {
    strNode *ptr = this->ingredients;
    //It constructs new string node which includes new ingredient
    strNode *new_node = new strNode(ingredient);
    //It checks for empty ingredient condition
    if (ptr == NULL) {
        this->ingredients = new_node;
    } else {
        while (ptr->nextNode()) {
            ptr = ptr->nextNode();
        }
        //It add new ingredient to the end of the list
        ptr->addStrNode(new_node);
    }
}

//Removes ingredient from the pizza
void Pizza::remove(const string &ingredient) {
    strNode *ptr = this->ingredients;
    //Checks first ingredient and if it finds, it returns.
    if (ptr->getString() == ingredient) {
        this->ingredients = ptr->nextNode();
        delete ptr;
        return;
    }
    //Searches for ingredient
    while (ptr->nextNode() && ptr->nextNode()->getString() != ingredient) {
        ptr = ptr->nextNode();
    }
    //If it cannot find it, function returns
    if (ptr->nextNode() == NULL) {
        return;
    }
    //If it finds, deletes the node from the ingredient list
    if (ptr->nextNode()->getString() == ingredient) {
        strNode *temp = ptr->nextNode();
        ptr->addStrNode(ptr->nextNode()->nextNode());
        delete temp;
    }
}

//Deconstructor
Pizza::~Pizza() {
    strNode *ptr = this->ingredients;
    //Iterates over the ingredients and deletes them
    while (ptr) {
        strNode *temp = ptr;
        ptr = ptr->nextNode();
        delete temp; //deletes ingredient
    }
    this->ingredients = NULL; //Assigns to a null
}

//Prints ingredients in proper forms
void Pizza::printIngredients() const {
    strNode *ptr = this->ingredients;
    //Iterates over the ingredients and prints contents of them
    while (ptr) {
        if (ptr->nextNode() == NULL)
            cout << ptr->getString(); //For last item it does not print comma
        else
            cout << ptr->getString() << ", ";

        ptr = ptr->nextNode();
    }
}

//Checks inside of the string and determines is it integer or not
bool isInteger(string in) {
	if(in.size()!=1 and in[0]=='0'){
        return false; //Checks inputs that are start with 0
    }
    for (unsigned i = 0; i < in.size(); i++) {
        int integer = in[i] - '0'; //It converts char to integer
        if (!(integer >= 0 and integer <= 9))
            return false; //If it is out of range it returns false
    }
    return true;
}

//The function converts strings to positive integer type
int string_to_integer(string in) {
    int res = 0; //It keeps result
    for (unsigned i = 0; i < in.size(); i++) {
        int integer = in[i] - '0'; //It converts char to integer
        res += pow(10, in.size() - i - 1) * integer; //It adds digit value to res
    }
    return res;
};
#endif //OOP1_PIZZA_H
