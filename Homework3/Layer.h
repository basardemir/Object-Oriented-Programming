/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 26/05/2020  */
#ifndef OOP3_LAYER_H
#define OOP3_LAYER_H
#include "Neurons.h"
#include "Vector.h"
#include <iostream>
#include <exception>

class Layer{
private:
    int neuron_number; //Number of neurons in this layer
    int next_layer_num; //Number of neurons in next layer
    Neuron** neuron_arr; //Dynamic array for keeping neurons
    double** weight_matrix;//2D Weight matrix between this layer to next layer
    double** b_matrix; //2D B matrix
public:
    //Constructors
    Layer(Vector* values, int n, int type, int next); //Constructor for first layer
    Layer(int n, int type, int next); //Constructor for layers

    Neuron** getNeuronArr() const; //Returns array of neurons
    double** getWeightMatrix() const; //Returns weight matrix
    double** getBVector() const; //Returns B matrix
    double** getAMatrix(); //Returns matrix of activated values of neurons
    double** getWA(); //Returns multiplication matrix of W and A
    int getNeuronNumber() const; //Returns neuron number of layer

    void SetNeurons(double** WA); //Sets z values of neurons and activates them
    void printAvalues() const; //Prints activated values of neurons

    ~Layer(); //Deconstructor
};

//Constructor for first layer
Layer::Layer(Vector *values, int n, int type, int next) {
    //Checks given type values
    if(!(type==0 or type==1 or type==2)){
        //If they are not valid, it throws exception
        throw "Unidentified activation function!";
    }
    int size = values->getSize();
    //Compares size of values vector and given size
    if(size!=n){
        //If they are not equal, it throws exception
        throw "Input shape does not match!";
    }

    this->b_matrix=NULL; //It sets B vector to
    this->next_layer_num=next; //It keeps neuron number of next layer
    this->neuron_number=n; //It keeps neuron number of the layer
    if(next==0){ //If it is single layer in network
        this->weight_matrix=NULL; //There is no weight matrix
    }
    else{
        this->weight_matrix= new double*[next]; //It initializes rows of weight matrix
        for(int k=0; k<next;k++){
            //It creates columns of wight matrix
            this->weight_matrix[k] = new double[n];
            for(int q=0;q<n;q++){
                //It fills matrix with 0.1 value
                this->weight_matrix[k][q]=0.1;
            }
        }
    }
    //It creates neuron array of the layer
    this->neuron_arr = new Neuron*[n];

    if(type==0){ //If type is Sigmoid
        for(int i=0; i<n;i++){
            neuron_arr[i] = new SigmoidNeuron(); //It creates Sigmoid Neuron
            neuron_arr[i]->set_z(values->getFromIndex(i)); //Takes z from values array
            neuron_arr[i]->set_a(values->getFromIndex(i)); //It activates corresponding neuron
        }
    }
    else if(type==1){//If type is ReLU
        for(int i=0; i<n;i++){
            neuron_arr[i] = new ReluNeuron();//It creates ReLU Neuron
            neuron_arr[i]->set_z(values->getFromIndex(i));//Takes z from values array
            neuron_arr[i]->set_a(values->getFromIndex(i));//It activates corresponding neuron
        }
    }
    else if(type==2){//If type is Leaky ReLU
        for(int i=0; i<n;i++){
            neuron_arr[i] = new LReluNeuron();//It creates Leaky ReLU Neuron
            neuron_arr[i]->set_z(values->getFromIndex(i));//Takes z from values array
            neuron_arr[i]->set_a(values->getFromIndex(i));//It activates corresponding neuron
        }
    }
}

//Constructor for layers
Layer::Layer(int n, int type, int next) {
    //Checks given type values
    if(!(type==0 or type==1 or type==2)){
        //If they are not valid, it throws exception
        throw "Unidentified activation function!";
    }
    this->next_layer_num=next;; //It keeps neuron number of next layer
    this->b_matrix = new double*[n]; //It creates rows of the B matrix
    this->neuron_number=n;//It keeps neuron number of the layer
    for(int j=0; j<n; j++){//It iterates over rows of B matrix
        this->b_matrix[j] = new double[1]; //It creates 1 column
        this->b_matrix[j][0] = 0.1; //It fills with 0.1 value
    }

    if(next!=0){//If it is not last matrix
        this->weight_matrix= new double*[next];//It initializes rows of weight matrix
        for(int k=0; k<next;k++){
            //It creates columns of wight matrix
            this->weight_matrix[k] = new double[n];
            for(int q=0;q<n;q++){
                //It fills matrix with 0.1 value
                this->weight_matrix[k][q]=0.1;
            }
        }
    }else{
        this->weight_matrix=NULL; //There is no weight matrix
    }

    //It creates neuron array of the layer
    this->neuron_arr = new Neuron*[n];

    if(type==0){//If type is Sigmoid
        for(int i=0; i<n;i++){
            neuron_arr[i] = new SigmoidNeuron();//It creates Sigmoid Neuron
        }
    }
    else if(type==1){//If type is ReLU
        for(int i=0; i<n;i++){
            neuron_arr[i] = new LReluNeuron();//It creates ReLU Neuron
        }
    }
    else if(type==2){//If type is Leaky ReLU
        for(int i=0; i<n;i++){
            neuron_arr[i] = new ReluNeuron();//It creates Leaky ReLU Neuron
        }
    }
}

//Returns array of neurons
Neuron** Layer::getNeuronArr() const {
    return neuron_arr;
}

//Returns weight matrix
double **Layer::getWeightMatrix() const {
    return weight_matrix;
}

//Returns B matrix
double** Layer::getBVector() const {
    return b_matrix;
}

//Returns matrix of activated values of neurons
double **Layer::getAMatrix() {
    //It creates 2D A array
    double** res = new double*[this->neuron_number];
    //It iterates over rows of A
    for(int i=0; i<this->neuron_number; i++){
        //It creates 1 sized column
        res[i] = new double[1];
        //It fills with activation value of neuron
        res[i][0]=this->neuron_arr[i]->get_a();
    }
    return res; //Returns array
}

//Sets z values of neurons and activates them
void Layer::SetNeurons(double **WA) {
    //It iterates over the neurons of layer
    for(int i = 0; i < this->neuron_number; i++){
        //It assignes z value by WA+B
        neuron_arr[i]->set_z(WA[i][0]+this->b_matrix[i][0]);
        //It activates neuron
        neuron_arr[i]->activate();
    }
    //It iterates over the ows of WA matrix
    for(int i = 0; i < this->neuron_number; i++)
        delete[] WA[i]; //Deletes row
    delete[] WA; //Deletes all matrix
}

//Returns multiplication matrix of W and A
double **Layer::getWA() {
    //It constructs WA matrix
    double **res = new double*[this->next_layer_num];
    //It creates A matrix using function
    double** a_matrix = this->getAMatrix();
    //It iterates over the rows of the res
    for(int i=0; i<this->next_layer_num;i++){
        res[i] = new double[1]; //It creates 1 sized column
        double val=0; //It initalize a temporary value
        //It performs matrix multiplication
        for(int j=0; j<this->neuron_number; j++){
            val+=this->weight_matrix[i][j]*a_matrix[j][0];
        }
        res[i][0]=val; //It assigns result to corresponding area of matrix
    }
    //It deletes a matrix
    for(int i = 0; i < this->neuron_number; i++)
        delete[] a_matrix[i];
    delete[] a_matrix;
    //It returns WA matrix
    return res;
}

//Prints activated values of neurons
void Layer::printAvalues() const{
    //It iterates over the neurons
    for(int i=0; i<this->neuron_number; i++){
        //It prints a values
        cout<<this->neuron_arr[i]->get_a()<<endl;
    }
}

//Returns neuron number of layer
int Layer::getNeuronNumber()const {
    return this->neuron_number;
}

//Deconstructor
Layer::~Layer() {
    //If B matrix is not empty
    if(this->b_matrix != NULL){
        //It iterates over the B matrix and deletes its elements
        for(int i=0; i<this->neuron_number; i++)
            delete[] this->b_matrix[i];
        delete[] this->b_matrix;
    }
    //It iterates over the neuron array and deletes neuron
    for(int i=0; i<this->neuron_number; i++){
        delete this->neuron_arr[i];
    }
    delete[] this->neuron_arr;
    //If weight matrix is not empty
    if(this->weight_matrix!=NULL){
        //It iterates over the weight matrix and deletes its elements
        for(int j=0; j<this->next_layer_num;j++){
            delete[] this->weight_matrix[j];
        }
        delete[] this->weight_matrix;
    }
}


#endif //OOP3_LAYER_H