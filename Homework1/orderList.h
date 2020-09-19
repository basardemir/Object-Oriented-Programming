/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 08/04/2020  */

#ifndef OOP1_ORDERLIST_H
#define OOP1_ORDERLIST_H

#include "order.h"


//It is used for storing head of orders and operating orders
class orderList {
private:
    int n; //Number of orders
    Order *orderHead;
public:
    //---------Constructor
    orderList();

    //---------Deconstructor
    ~orderList();

    //---------General order operations
    //Starts to taking order
    bool takeOrder();

    //Adds new order to end of the list
    void addOrder(Order *);

    //Lists all orders
    void listOrders() const;

    //Starts to delivering operations
    void deliverOrders();

    //Finds index of order of the given customer order
    const int indexFinder(const string *name);

    //---------Drink order operations
    //Function which takes drink order
    drink_node *orderDrink();

    //Function which adds drinks to the drink section
    void addDrink(const string *drink, drink_node *drink_head);

    //Function for canceling all drink orders
    void deleteAllDrinks(drink_node *drink_head);

    //---------Pizza order operation
    //Function which takes pizza order
    pizza_node *orderPizza();

    //Function which adds pizzas to the pizza_head
    void addPizza(pizza_node *pizza_head, const Pizza *pizza,  const int amount);

};

//Constructor
orderList::orderList() {
    this->n = 0;
    this->orderHead = NULL;
}

//Deconstructor
orderList::~orderList() {
    //Iterates over the orders and deletes them
    Order *ptr = orderHead;
    while (ptr) { //It iterates over the orders
        Order *temp = ptr;
        ptr = ptr->nextOrder();
        delete temp; //Deletes order class
    }
    delete ptr;
    this->n = 0; //Sets number of orders as zero
}


//Function which takes new order
bool orderList::takeOrder() {
    //It takes new pizza order
    pizza_node *pizza = orderPizza();
    if (!pizza) {
        return false; //If user does not want any pizza
    };
    //It takes new drink order
    drink_node *drink = orderDrink();

    //It takes customer name
    string name;
    cout << "Please enter your name:";
    //Checks customer name condition
    while (true) {
        getline(cin, name); //Gets user input
        cin.clear(); //Clears buffer
        if(name.empty()) {
            cout << "Your input is not valid. Please enter proper input:" << endl;
            continue;
        }
        int search = indexFinder(&name); //Returns -1 if it does not find name in orders.
        if (search == -1) {
            break; //It cannot find order with same name
        } else {
            //It finds order with same name and prints error message
            cout << "This customer name is used, please write another name" << endl;
        }
    }

    //Constructs order class respect to demand for drink and add it to the order list
    Order *ptr;
    if (drink == NULL) {
        ptr = new Order(name, pizza); //Constructs new order without drink
        addOrder(ptr);
    } else {
        ptr = new Order(name, pizza, drink); //Constructs new order with drink
        addOrder(ptr);
    }
    cout << "Your order is saved, it will be delivered when it is ready..." << endl;
    //Prints the order which is taken
    ptr->printOrder();
    this->n++; //Increments number of orders in the class
    return true; //It returns true
}

//Function which takes drink order
drink_node *orderList::orderDrink() {
    //It begins to printing menu
    cout << "Please choose a drink" << endl;
    string *drinks = new string[5]; //It initialize drinks array
    drinks[0] = "no drink (Cancel all drink orders and saves it)"; //For information
    drinks[1] = "cola";
    drinks[2] = "soda";               //Filled with proper drink names
    drinks[3] = "ice tea";
    drinks[4] = "fruit juice";

    string *prices = new string[5];  //It initialize prices array
    prices[0] = ""; //For aligning indexes with drinks array
    prices[1] = "4 TL";
    prices[2] = "2 TL";            //Filled with corresponding drink prices
    prices[3] = "3 TL";
    prices[4] = "3.5 TL";

    //It prints drink options and their prices
    for (int i = 0; i < 5; i++) {
        cout << i << ". ";
        cout << drinks[i];
        cout << " " << prices[i] << endl;
    }
    cout<<"Press -1 for save your order"<<endl;

    int drink; //User's drink choice
    string input; //User's input
    drink_node *drink_head = NULL; //Initialize drink head as a null
    bool flag = true; //For loop control
    while (true) {
        getline(cin, input); //Takes user's input
        cin.clear(); //Clears buffer
        if(input.empty()) {
            cout << "Input is at out of range or not valid" << endl;
            continue;
        }
        if (input == "-1")
            break; //Finishes taking drink order
        if (input == "0") {
            deleteAllDrinks(drink_head);
            drink_head = NULL; //It deletes all drinks which have already ordered
            break;  //Finishes taking drink order
        }
        bool check = isInteger(input); //Checks suitability of the input
        if (check) {
            drink = string_to_integer(input); //Converts input to integer
            if (drink == 0) {
                deleteAllDrinks(drink_head);
                drink_head = NULL; //It deletes all drinks which have already ordered
                break;  //Finishes taking drink order
            }
            if (drink < 0 or drink > 4) {  //Checks input range
                cout << "Your input out of range" << endl;
            } else {
                if (flag) {
                    //It initializes drink head and adds drink
                    string new_drink(drinks[drink]); //It takes name of the drink
                    drink_head = new drink_node(new_drink, 1); //Constructs drink_node
                    flag = false; //For first input checking
                } else {
                    //Adds drinks to the list
                    string new_drink(drinks[drink]); //It takes name of the drink
                    addDrink(&new_drink, drink_head); //Adds to the drink list
                }
            }
        } else {
            //Error message
            cout << "Your input is not valid. Please enter proper input:" << endl;
        }
    }
    delete[] drinks; //Deletes drinks array
    delete[] prices; //Deletes prices array
    return drink_head;
}

//Function which adds drinks to the drink section
void orderList::addDrink(const string *drink, drink_node *drink_head) {
    drink_node *ptr = drink_head;
    //Checks availability of the drink head
    if (drink_head == NULL) {
        drink_head = new drink_node(*drink, 1);
        return;
    }
    //Iterates over all drinks and checks if it was added before
    while (ptr->nextNode()) {
        //If it has already added, it increases amount of drink
        if (ptr->getName() == *drink) {
            ptr->addAmount();
            return;
        }
        ptr = ptr->nextNode();
    }
    //Checks last element of drink list
    if (ptr->getName() == *drink) {
        ptr->addAmount();
        return;
    } else {
        //If it does not find it, it adds new drink to the end of the list
        drink_node *new_drink = new drink_node(*drink, 1); //Constructs new node
        ptr->addDrinkNode(new_drink); //Adds as a last element
    }
}


//Function which takes pizza order
pizza_node *orderList::orderPizza() {
    //Prints pizza options
    cout << "Pizza Menu" << endl;
    cout << "1. Chicken Pizza (mozarella, chicken, mushroom, corn, onion, tomato)" << endl;
    cout << "2. Broccoli Pizza (mozarella, broccoli, pepperoni, olive, corn, onion)" << endl;
    cout << "3. Sausage Pizza (mozarella, sausage, tomato, olive, mushroom, corn)" << endl;
    cout << "0. Back to main menu" << endl;
    int pizza_type = 0;
    string input; //User's input
    bool flag = true; //For loop checking
    //Takes user input for pizza selection
    while (flag) {
        getline(cin, input); //Takes user's input
        cin.clear(); //Clears buffer
        //It classifies user inputs and determines pizza type which is ordered by user
        if (input == "1") {
            pizza_type = 1; //Determines pizza type
            flag = false;
        } else if (input == "2") {
            pizza_type = 2; //Determines pizza type
            flag = false;
        } else if (input == "3") {
            pizza_type = 3; //Determines pizza type
            flag = false;
            //Returns to the main menu
        } else if (input == "0") {
            return NULL;
        } else {
            //Prints error message
            cout << "Please enter proper input:" << endl;
        }
    }
    //Prints size types and takes input
    cout << "Select size: small (15 TL), medium (20 TL), big (25 TL)" << endl;
    string size; //For keeping user input
    flag = true; //For breaking loop
    while (flag) {
        getline(cin, size); //Gets user input
        cin.clear(); //Cleans buffer
        if (!(size == "small" or size == "medium" or size == "big")) { //Checks user input for validation
            cout << "Please enter proper input:" << endl; //Prints error message
        } else {
            flag = false; //Breaks loop
        }
    }
    //Prints crust types and takes input
    cout << "Select crust type: thin, normal, thick" << endl;
    string crust_type; //For keeping user input
    flag = true; //For breaking loop
    while (flag) {
        getline(cin, crust_type);//Gets user input
        cin.clear();//Cleans buffer
        if (!(crust_type == "thin" or crust_type == "normal" or crust_type == "thick")) {//Checks user input for validation
            cout << "Please enter proper input:" << endl;//Prints error message
        } else {
            flag = false; //Breaks loop
        }
    }
    //Takes amount of pizza that is wanted
    int amount = 0;
    cout << "Enter amount:";
    string amount_input;

    //Checks input and assigns it to the amount
    flag = true;
    while (flag) {
        getline(cin, amount_input);//Gets user input
        bool check = isInteger(amount_input); //Checks string to determine it is integer or not
        if (check) {
            amount = string_to_integer(amount_input); //Converts string to integer
            if (amount <= 0) {
                cout << "Please enter proper input:" << endl; //Checks range
            }
            //Pizza amount is restricted to prevent high memory usage
            else if (amount > 30) {
                cout << "Only 30 pizzas can be ordered at the same time" << endl;
            } else {
                flag = false; //Breaks while loop
            }
        } else {
            cout << "Please enter proper input:" << endl; //Prints error message for non-integer inputs
        }
    }
    //Constructs a model pizza according to user inputs
    Pizza *pizza = new Pizza(size, crust_type, pizza_type);
    pizza_node *pizza_head = new pizza_node(pizza); //Adds first pizza corresponding to model pizza

    //The function adds extra ordered pizzas to the order
    addPizza(pizza_head, pizza, amount);

    return pizza_head;
}

void orderList::addPizza(pizza_node *pizza_head, const Pizza *pizza, const int amount) {
    //It starts to make pizzas as user wants
    pizza_node *ptr = pizza_head;
    for (int i = 0; i < amount - 1; i++) {
        cout << i + 1 << ".";
        //New pizza initializes with copy constructor
        Pizza *pizza_make = new Pizza(*pizza);
        //Asks for undesirable ingredients
        pizza_make->removeIngredient();
        //New pizza is added to the pizza list
        pizza_node *new_pizza = new pizza_node(pizza_make);
        ptr->addPizzaNode(new_pizza);
        ptr = ptr->nextNode();
    }
}


//Function which add orders to the order list
void orderList::addOrder(Order *order) {
    Order *ptr = orderHead;
    if (ptr == NULL) { //For empty order list
        orderHead = order; //Adds as a order head
        return;
    }
    while (ptr->nextOrder()) //Iterates to end of the linked list
        ptr = ptr->nextOrder();

    ptr->addOrder(order); //Adds new order to end of the linked list
}

//Function which lists all orders in proper form
void orderList::listOrders() const {
    Order *ptr = orderHead;
    if (ptr == NULL) { //For empty order list it prints proper output
        cout << "-------------" << endl;
        cout << "There is no orders to list" << endl;
        cout << "-------------" << endl;
        return;
    }
    int i = 1;
    while (ptr) { //It iterates over the whole orders
        cout << i << endl;
        ptr->printOrder(); //Prints order content
        ptr = ptr->nextOrder();
        i++;
    }
}

//Function which operates order deliver system
void orderList::deliverOrders() {
    //Checks order number for availability
    if (this->n == 0) { //For empty order list it prints proper output
        cout << "-------------" << endl;
        cout << "There is no orders to deliver" << endl;
        cout << "-------------" << endl;
        return;
    }

    //Lists orders and asks for customer name
    listOrders();
    cout << "Please write the customer name in order to deliver his/her order: " << endl;
    string name; //Keeps customer name
    getline(cin, name); //Takes user input

    while(true){
        if(name.empty()) {
            cout << "Input is not valid" << endl;
            cout << "Please write the customer name in order to deliver his/her order: " << endl;
            getline(cin, name); //Takes user input
            cin.clear(); //Clears buffer
        } else{
            break;
        }
    }
    //Searches orders to find correct order, and returns index
    int index = indexFinder(&name);
    //If there is no order with this name, it shows alert message
    if (index == -1) {
        cout << "-------------" << endl;
        cout << "There is no orders which name is " << name << " to deliver" << endl;
        cout << "-------------" << endl;
        return;
    }

    //Prints message for delivering orders
    cout << "Following order is delivering..." << endl;
    Order *ptr = orderHead;

    //Finds pointer of the order, and separates order from the list
    if (index == 0) { //In case of order which will be delivered is the head order
        ptr->printOrder(); //Prints its contents
        orderHead = ptr->nextOrder(); //Assigns new head order
    } else {
        int count = 0;
        while (count + 1 != index) { //It reaches one node before from the demanded order
            ptr = ptr->nextOrder();
            count++;
        }
        ptr->nextOrder()->printOrder(); //Prints its contents
        Order *temp = ptr->nextOrder(); //Assigns prt to delivered order
        ptr->addOrder(ptr->nextOrder()->nextOrder()); //It separates delivered order from the linked list
        ptr = temp;
        temp = NULL;
    }

    //It prints price and asks for promotion code
    cout << "Total price: " << ptr->getPrice() << "TL" << endl;
    cout << "Do you have promotion code? (y/n)" << endl;
    string code; //Keeps user input y/n
    bool flag = true;
    while (flag) {
        getline(cin, code); //Takes user input
        cin.clear(); //Clears buffer
        if (code == "y") {
            cout << "Enter your promotion code" << endl;
            string promo; //Keeps promotion code
            getline(cin, promo);//Takes user input
            cin.clear();//Clears buffer
            //If user enters correct input, price decreases
            if (promo == "I am a student") {
                cout << "-------------" << endl;
                cout << "Your new price is " << ptr->getPrice() / 10.0 * 9 << "TL" << endl; //Prints discounted print
                cout << "The order is delivered successfully!" << endl;//Prints success message
                cout << "-------------" << endl;
                flag = false;
                break;
            } else {
                //Prints wrong promotion code message
                cout << "Your code is wrong sorry..." << endl;
                cout << "Do you have promotion code? (y/n)" << endl; //Asks one more time
            }
        } else if (code == "n") {
            cout << "-------------" << endl;
            cout << "The order is delivered successfully!" << endl; //Prints success message
            cout << "-------------" << endl;
            flag = false;
        } else {
            cout << "Please enter y or n:" << endl; //Error output
        }
    }
    //Deletes order
    delete ptr;
    //Updates number of all orders
    this->n--;
}

//Function which returns index of the order by customer name
int const orderList::indexFinder(const string *name) {
    Order *ptr = orderHead;
    int count = 0;
    while (ptr) { //Iterates over the all orders
        if (ptr->getName() == *name) {
            return count; //Returns index counter
        }
        count++; //Increments counter
        ptr = ptr->nextOrder();
    }
    //If it does not find, it returns -1
    return -1;
}


//Function for canceling all dirnk orders
void orderList::deleteAllDrinks(drink_node *drink_head) {
    drink_node *ptr = drink_head;
    while (ptr) { //It traverses all drink nodes
        drink_node *temp = ptr;
        ptr = ptr->nextNode();
        delete temp; //Deletes drink nodes
    }
    drink_head = NULL; //Assigns null pointer to the drink head
}

#endif //OOP1_ORDERLIST_H