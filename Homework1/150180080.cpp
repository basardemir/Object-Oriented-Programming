/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 08/04/2020 */
#include <iostream>
#include "orderList.h"

using namespace std;

int main() {
    bool flag = true;
    //Constructs order list
    orderList list = orderList();
    while (flag) {
        //Prints main menu
        cout << "Welcome to Unicorn Pizza!" << endl;
        cout << "1. Add an order" << endl;
        cout << "2. List orders" << endl;
        cout << "3. Deliver order" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose what to do:";
        string choose;
        getline(cin, choose); //It takes user input
        cin.clear();
        if (choose == "1")
            list.takeOrder(); //Calls function for taking order
        else if (choose == "2")
            list.listOrders(); //Calls function for listing all orders
        else if (choose == "3")
            list.deliverOrders(); //Calls function for delivering operations
        else if (choose == "4") {
            flag = false;         //Exits programme
            cout << "Goodbye..." << endl;
        } else {
            cout << "Your input is wrong. Please enter valid input" << endl; //Prints error output
        }
    }
    return 0;
}
