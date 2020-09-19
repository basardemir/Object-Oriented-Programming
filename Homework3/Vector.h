/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 26/05/2020  */
#ifndef OOP3_VECTOR_H
#define OOP3_VECTOR_H
//Vector class which keeps double values
class Vector{
private:
    double* arr; //Dynamic double array
    int size; //Keeps the number of elements
    int capacity;//Keeps the size of the array
public:
    //Constructor
    Vector();

    //Getters
    int getSize(); //Returns size of the vector
    double getFromIndex(int i); //Returns the value which stores in given index

    void push(double val); //Adds new value to array

    //Deconstructor
    ~Vector();
};

//Constructor
Vector::Vector() {
    //Initializes dynamic array with 1 capacity
    arr = new double[1];
    size=0;
    capacity=1;
}

//Deconstructor
Vector::~Vector() {
    delete[] arr; //Deletes dynamic array
}

//Adds new value to array
void Vector::push(double val) {
    if(capacity==size){//If capacity of the array is full
        double *n_arr= new double[capacity*2]; //It creates new array with 2 times capacity
        //It copies contents of old array
        for(int i=0; i<size;i++){
            n_arr[i]=this->arr[i];
        }
        delete[] this->arr; //Deletes ol array
        this->arr=n_arr; //Assigns new array to class
        this->capacity*=2; //updates capacity
    }
    this->arr[size]=val; //Adds new value to end of array
    size++;//Increments size
}

//Returns size of the vector
int Vector::getSize() {
    return this->size;
}

//Returns the value which stores in given index
double Vector::getFromIndex(int i) {
    return this->arr[i];
}


#endif //OOP3_VECTOR_H
