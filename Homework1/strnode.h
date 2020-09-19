/* @Author
Student Name: Başar Demir
Student ID: 150180080
Date: 08/04/2020  */
#ifndef OOP1_STRNODE_H
#define OOP1_STRNODE_H

#include <string>

using namespace std;

//String Node class is used for storing ingredients of pizzas
class strNode {
private:
    string str;
    strNode *next;
public:
    //---------Constructor
    strNode(string);

    //---------Getters and setters
    string getString() const;

    strNode* nextNode() const;

    void addStrNode(strNode*);
};

//Constructor
strNode::strNode(const string str_in) {
    this->str = str_in;
    this->next = NULL;
}

//Returns stored string of node
string strNode::getString() const{
    return this->str;
}
//Returns pointer of the next node
strNode *strNode::nextNode() const{
    return this->next;
}
//Adds new node to next of current node
void strNode::addStrNode(strNode* node) {
    this->next=node;
}

#endif //OOP1_STRNODE_H