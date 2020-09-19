/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 26/05/2020  */
#ifndef OOP3_NEURONS_H
#define OOP3_NEURONS_H
#include <cmath>
using namespace std;

//The abstract base class for keeping Neurons
class Neuron{
protected:
    double z; //Value
    double a; //Activated value
public:
    //Constructors
    Neuron();
    Neuron(double z, double a);
    Neuron(double z);

    //Virtual Activation function
    virtual void activate() = 0;

    //Getters
    double get_a() const;
    double get_z() const;

    //Setters
    void set_z(const double z);
    void set_a(const double a);

    //Virtual Deconstructor
    virtual ~Neuron();
};

//Default Constructor
Neuron::Neuron() {
    //Initializes a and z values as 0
    this->z=0;
    this->a=0;
}

//Constructor
Neuron::Neuron(double z, double a) {
    //Initializes a and z values with given values
    this->z=z;
    this->a=a;
}

//Constructor
Neuron::Neuron(double z) {
    //Initializes a with 0 and z value with given values
    this->z=z;
    this->a=0;
}

//Returns a value of Neuron
double Neuron::get_a() const{
    return this->a;
}

//Returns z value of Neuron
double Neuron::get_z() const{
    return this->z;
}

//Sets z value with given parameter
void Neuron::set_z(const double z) {
    this->z=z;
}

//Sets a value with given parameter
void Neuron::set_a(const double a) {
    this->a=a;
}
//Default Constructor
Neuron::~Neuron() {}

//Sigmoid Neuron Class which is derived from Neuron Class
class SigmoidNeuron:public Neuron{
public:
    SigmoidNeuron(); //Default Constructor
    void activate(); //Virtual Activation function
};

//Activation function
void SigmoidNeuron::activate() {
    //Sets a value with Sigmoid Function
    this->a= (1/(1+exp(-this->get_z())));
}

//Default Constructor
SigmoidNeuron::SigmoidNeuron():Neuron() {}

//ReLU Neuron Class which is derived from Neuron Class
class ReluNeuron:public Neuron{
public:
    ReluNeuron();//Default Constructor
    void activate();//Virtual Activation function
};

//Activation function
void  ReluNeuron::activate() {
    //Sets a value with corresponding ReLU function
    this->a= max(0.0,this->get_z());
}

//Default Constructor
ReluNeuron::ReluNeuron():Neuron() {}

//Leaky ReLU Class which is derived from Neuron Class
class LReluNeuron:public Neuron{
public:
    LReluNeuron();//Default Constructor
    void activate();//Virtual Activation function
};

//Activation function
void  LReluNeuron::activate() {
    //Sets a value with corresponding Leaky ReLU function
    this->a= max(0.1*this->get_z(), this->get_z());
}
//Default Constructor
LReluNeuron::LReluNeuron():Neuron() {}

#endif //OOP3_NEURONS_H
