/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 26/05/2020  */
#ifndef OOP3_NETWORK_H
#define OOP3_NETWORK_H
#include "Layer.h"
#include "Vector.h"
class Network{
private:
    int LayerNumber; //It keeps number of the layers that are in network
    Layer** layers;//Dynamic layer pointer array
public:
    //Constructor
    Network(int layer_num, int* neuron_nums,int* neuron_types, Vector* first_layer);

    void CalculateValues(); //Calculates a values of all neurons
    void Print() const; //Prints the network

    //Deconstructor
    ~Network();
};

//Constructor
Network::Network(int layer_num, int *neuron_nums, int *neuron_types, Vector* first_layer) {
    int counter=0; //It keeps the value of registered layers without error
    try {
        this->LayerNumber = layer_num; //It assigns number of layers
        this->layers = new Layer *[layer_num];//It constructs layer pointer array
        bool flag = false; //First layer flag
        for (int i = 0; i < layer_num; i++) {//It iterates up to layer number
            if (flag == 1) {//If it is not first layer
                if (i + 1 != layer_num) //If it is not last layer
                    //It constructs layer
                    this->layers[i] = new Layer(neuron_nums[i], neuron_types[i], neuron_nums[i + 1]);
                else { //It constructs layer with 0 next value
                    //It constructs layer with 0 next value
                    this->layers[i] = new Layer(neuron_nums[i], neuron_types[i], 0);
                }
            } else {//First layer
                if (i + 1 != layer_num)//It constructs firts layer
                    this->layers[i] = new Layer(first_layer, neuron_nums[i], neuron_types[i], neuron_nums[i + 1]);
                else {//It constructs layer with 0 next value
                    //It constructs first layer with 0 next value
                    this->layers[i] = new Layer(first_layer, neuron_nums[i], neuron_types[i], 0);
                }
                flag = true; //It updates flag
            }
            counter++; //Increments counter
        }
    }
    catch (const char* error) { //If any exception is caught
        for(int i=0;i<counter;i++) //It iterates over already constructed layers
            delete this->layers[i]; //Deletes layer
        delete[] this->layers; //Deletes layer array
        throw error; //Throws caught error
    }
}

//Calculates a values of all neurons
void Network::CalculateValues() {
    //It iterates over the layers
    for(int i=1; i<this->LayerNumber;i++){
        Layer* ptr = this->layers[i]; //Keeps pointer of the layer
        ptr->SetNeurons(this->layers[i-1]->getWA());//It sets the neurons
    }
}

//Prints the network
void Network::Print() const {
    //It iterates over the layers
    for(int i=0; i<this->LayerNumber;i++){
        cout<<"Layer "<<i <<":"<<endl;
        Layer* ptr = this->layers[i]; //Keeps pointer of the layer
        ptr->printAvalues(); //Call A value print function
    }
}
//Deconstruction
Network::~Network() {
    //It iterates over the layers
    for(int i=0; i<this->LayerNumber;i++){
        delete this->layers[i];//Deletes layer
    }
    delete[] this->layers; //Deletes layer array
}


#endif //OOP3_NETWORK_H