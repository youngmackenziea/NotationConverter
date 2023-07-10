#include "NotationConverter.hpp"

using namespace std;

//converts string in postfix notation to infix notation
string NotationConverter::postfixToInfix(string inStr) {
    if(!isalpha(inStr[0])) { //throw is first element is not a letter
        throw inStr;
    }

    for(unsigned int i = 0; i < inStr.size(); i++) {
        if(inStr[i] != ' ') { //checks for whitespace
            if(inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/') { //if element is an operator, add to back of temporary deque
                temp2.insertBack(inStr[i]);
            }
            else { //else, add operand to different temporary deque
                temp1.insertBack(inStr[i]); 
            }
        }
    }

    if(temp2.size() != temp1.size() - 1) { //compares number of operands and operators
        throw inStr;
    }
    
    mainDeque.insertBack('(');

    int temp2Size = temp2.size(); //size of operator deque
   
    for(int i = 1; i < temp2Size - 1; i++) { //number of parentheses depends on number of operators
            mainDeque.insertBack('(');
    }

    
    while(temp1.empty() == false) { //while operand deque is not empty...
        mainDeque.insertBack(temp1.front()); //...add operand to back of main deque...
        temp1.removeFront(); //...and remove from temporary deque

        if(temp2.empty() == false) { //if operator deque is not empty
            if(temp2.size() == 2) { //if there are two operators left
                mainDeque.insertBack(')'); 
                mainDeque.insertBack(temp2.back()); //insert back element into back of main deque
                temp2.removeBack(); //remove from temporary deque
                mainDeque.insertBack('(');
            }
            else {
                mainDeque.insertBack(temp2.front()); //insert back element into front of main deque
                temp2.removeFront(); //remove from temporary deque
            }
        }
    }

    mainDeque.insertBack(')');

    for(int i = 1; i < temp2Size - 1; i++) { //inserts needed parentheses
            mainDeque.insertBack(')');
    }

    return toString(); //calls toString() to convert final output
}

//converts string in postfix notation to prefix notation using infixToPrefix
string NotationConverter::postfixToPrefix(string inStr) {
    return infixToPrefix(postfixToInfix(inStr));
}

//converts string in infix notation to postfix notation
string NotationConverter::infixToPostfix(string inStr) {
    if(inStr[0] != '(') { //throw if first element isn't a parentheses
        throw inStr;
    }
    
    for(unsigned int i = 0; i < inStr.size(); i++) {
        while(inStr[i] != ')' && inStr[i] != *inStr.end()) { 
            if(inStr[i] != ' ') { //checks for whitespace
                if(inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/') { //if element is an operator, add to temporary deque
                        temp1.insertBack(inStr[i]);
                }
                else if(inStr[i] != '(') { //adds operands to main deque
                    mainDeque.insertBack(inStr[i]);
                }
            }
            i++; //update statement for while loop
        }

        int temp1Size = temp1.size(); //temporary deque's size
        for(int i = 0; i < temp1Size; i++) { //to maintain postfix order
            if(temp1.size() == 2) { //if there are two operators left, add back element to main deque
                mainDeque.insertBack(temp1.back());
                temp1.removeBack(); //remove from temporary deque
            }
            else { //add front operator to main deque
                mainDeque.insertBack(temp1.front());
                temp1.removeFront(); //remove from temporary deque
            }
        }
    }
    return toString(); //calls toString() to convert final output
}

//converts string in infix notation to prefix notation
string NotationConverter::infixToPrefix(string inStr) {
    if(inStr[0] != '(') { //throw is first element is not parentheses
        throw inStr;
    }
    for(unsigned int i = 0; i < inStr.size(); i++) { 
        while(inStr[i] != ')' && inStr[i] != *inStr.end()) {
            if(inStr[i] != ' '){ //checks for whitespace
                if(inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/') { //if element is an operator, add to main deque
                    if(inStr[i-2] == ')') { //if operator is next to closing parentheses, insert at front of main deque
                        mainDeque.insertFront(inStr[i]); 
                    }
                    else { //else, add to back of main deque
                        mainDeque.insertBack(inStr[i]);
                    }
                }
                else if(inStr[i] != '(') { //add operands to temporary deque
                    temp1.insertBack(inStr[i]);
                }
            }
            i++; //update statement for while loop
        }

        int temp1Size = temp1.size(); //temporary deque size
        for(int i = 0; i < temp1Size; i++) {
            mainDeque.insertBack(temp1.front()); //add temporary deque elements to main deque
            temp1.removeFront(); //remove from temporary deque
        }
    }
    return toString(); //calls toString() to convert final output
}

//converts string from prefix notation to infix notation
string NotationConverter::prefixToInfix(string inStr) {
    if(inStr[0] != '+' && inStr[0] != '-' && inStr[0] != '*' && inStr[0] != '/') { //throw is first element is not an operator
        throw inStr;
    }

    bool needParen = false; //is closing parentheses needed?
    int numParen = 0; //counts number of parentheses, needs to be even

    for(unsigned int i = 0; i < inStr.size(); i++) {
        if(inStr[i] != ' ') { //checks for whitespace
            if(inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '*' || inStr[i] == '/') { //if element is an operator
                temp1.insertBack(inStr[i]); //add to temporary deque
                mainDeque.insertBack('('); //add opening parentheses to main deque
                numParen++; //increment parentheses count
                needParen = false;  //closing parentheses only needed after operand
            }
            else { //insert operand to main deque
                mainDeque.insertBack(inStr[i]);

                if(needParen == true) {
                    mainDeque.insertBack(')'); //add closing parentheses to main deque
                    numParen--; //decrement number of parentheses
                }

                if(temp1.empty() == false) { //if temporary deque is not empty
                    mainDeque.insertBack(temp1.back()); //insert to back of main deque
                    temp1.removeBack(); //remove from temporary deque
                    needParen = true;   //closing parentheses needed
                }
            }
        }
    }

    if(numParen != 0) { //if number of parentheses is not even
        while(numParen != 0) {
            mainDeque.insertBack(')'); //insert closing parentheses to main deque
            numParen--; //decrement number of parentheses
        }
    }

    return toString(); //calls toString() to convert final output
}

//converts string in prefix notation to postfix notation using infixToPostfix
string NotationConverter::prefixToPostfix(string inStr) {
    return infixToPostfix(prefixToInfix(inStr));
}

//removes elements from deque and converts them to a string
string NotationConverter::toString() {
    string newStr;

    if(mainDeque.empty() == true) { //checks if deque is empty
        return newStr;
    }

    int dequeSize = mainDeque.size(); //size of deque

    for(int i = 0; i < dequeSize; i++) {
        if(mainDeque.front() == ')') { //if element is closing parentheses
            newStr.pop_back(); //remove whitespace between parentheses and operand
        }

        newStr += mainDeque.front(); //add deque element to string

        if(mainDeque.front() != '(') { //adds space unless it is before an opening parentheses
            newStr += ' ';
        }

        mainDeque.removeFront(); //remove element from deque
    }

    newStr.pop_back(); //removes extra space added in loop

    return newStr; //returns string of deque elements
}
