#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include "NotationConverterInterface.hpp"
#include "deque.hpp"
#include<iostream>

using namespace std;

class NotationConverter:public NotationConverterInterface {
    public:
        string postfixToInfix(string inStr); //converts string from postfix notation to infix notation
        string postfixToPrefix(string inStr); //convertes string from postfix notation to prefix notation
        string infixToPostfix(string inStr); //converts string from infix notation to postfix notation
        string infixToPrefix(string inStr); //converts string from infix notation to prefix notation
        string prefixToInfix(string inStr); //converts string from prefix notation to infix notation
        string prefixToPostfix(string inStr); //converts string from prefix notation to postfix notation
        string toString(); //removes elements from deque and converts them to a string

    private:
        Deque mainDeque; //main deque
        Deque temp1; //temporary deque
        Deque temp2; //temporary deque
};

#endif