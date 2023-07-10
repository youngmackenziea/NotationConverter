#ifndef DEQUE_H
#define DEQUE_H

class DNode {
    private:
    char elem; //char node element value
    DNode* prev; //pointer to previous node
    DNode* next; //pointer to next node
friend class LinkedList; //allows LinkedList class to access these variables
};

class LinkedList {
public:
    LinkedList(); //constructor
    ~LinkedList(); //desctructor
    bool empty() const; //is list empty?
    const char& front() const; //return character in first node
    const char& back() const; //return character in last node
    void addFront(const char& e); //add to front of list
    void addBack(const char& e); //add to back of list
    void removeFront(); //remove from front
    void removeBack(); //remove from back
protected:
    void addNode(DNode* v, const char& e); //adds a new node before v
    void removeNode(DNode* v); //remove node v
private:
    DNode* header; //points right before first node
    DNode* trailer; //points right after last node
};

class Deque {
public:
    int size() const; //returns size of deque
    bool empty() const; //is deque empty?
    const char& front(); //returns front element of deque
    const char& back(); //returns back element of deque
    void insertFront(const char& e); //add to front of deque
    void insertBack(const char& e); //add to back of deque
    void removeFront(); //remove from front
    void removeBack(); //remove from back
private:
    LinkedList deq;
    int n = 0; //initial size of deque is 0
friend class NotationConverter; //allows NotationConverter to access all of Deque's private members
};

#endif