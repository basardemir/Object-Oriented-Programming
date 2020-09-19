/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 26/05/2020  */

#include <iostream>
#include "Network.h"
#include <fstream>
#include <string>
#include <sstream>


int main(int argc, char *argv[]) {
    int layer_num; //It keeps number of layers
    int *neuron_nums; //It keeps neuron number of each layer
    int *neuron_types; //It keeps neuron type of each layer
    Vector *first_layer = new Vector(); //It keeps z values of first layer

    string text_input; //Temporary storage for inputs

    ifstream file(argv[1]); //It opens the file

    int counter = 0; //It counts input types

    while (getline(file, text_input)) { //While it is not end of the file
        stringstream s(text_input); //It returns input to string stream
        double value; //Temporary storage for numerical inputs
        if (counter == 0) { //If it is for layer number
            s >> layer_num; //It takes layer number
            neuron_nums = new int[layer_num]; //It allocates memory for neuron numbers array
            neuron_types = new int[layer_num];//It allocates memory for neuron types array
        }
        if (counter == 1) {//If it is for neuron numbers
            int a = 0; //It sets iterator to 0
            while (s >> value) { //Reads value from string stream
                neuron_nums[a] = value; //Assigns to corresponding index
                a++; //Increments iterator
            }
        }
        if (counter == 2) {//If it is for neuron types
            int a = 0;//It sets iterator to 0
            while (s >> value) {//Reads value from string stream
                neuron_types[a] = value;//Assigns to corresponding index
                a++;//Increments iterator
            }
        }
        if (counter == 3) {//If it is for first layer's initial values
            int a = 0;//It sets iterator to 0
            while (s >> value) {//Reads value from string stream
                first_layer->push(value); //It adds value to first layer vector
                a++;//Increments iterator
            }
        }
        counter++;//Increments counter
    }
    try {//It tries to construct network
        //It calls network constructor
        Network *ptr = new Network(layer_num, neuron_nums, neuron_types, first_layer);
        //It calculates a values of neurons
        ptr->CalculateValues();
        //It prints results
        ptr->Print();
        //Deletes network
        delete ptr;
    }
    catch (const char *error) { //If any error occures
        cout << error << endl; //It prints the error meesage
    }

    file.close();//It closes file

    delete[] neuron_nums; //Deletes neuron numbers array
    delete[] neuron_types;//Deletes neuron types array
    delete first_layer;//Deletes neuron first layer vector

    return 0;
}
