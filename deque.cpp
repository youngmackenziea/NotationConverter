#include "deque.hpp"

//functions for LinkedList class

LinkedList::LinkedList() { //constructor
    header = new DNode; //allocates memory for sentinel header
    trailer = new DNode; //alloactes memory for sentinel trailer
    header -> next = trailer; //points header and trailer to eachother
    trailer -> prev = header;
}

LinkedList::~LinkedList() { //destructor
    while(!empty()) { //while list is not empty, remove the front element
        removeFront();
    }
    delete header; //deallocates memory for header
    delete trailer; //deallocates memory for trailer
}

bool LinkedList::empty() const { //is list empty?
    return (header -> next == trailer); //if header points to trailer, list is empty
}

const char& LinkedList::front() const { //return character in front node
    return header -> next -> elem;
}

const char& LinkedList::back() const { //return character in back node
    return trailer -> prev -> elem;
}

void LinkedList::addNode(DNode* v, const char& e) { //adds a new node before v 
    DNode* u = new DNode;
    u -> elem = e; //creates new node for e
    u -> next = v; //link u in between v...
    u -> prev = v -> prev; //...and v -> prev
    v -> prev -> next = v -> prev = u;
}

void LinkedList::addFront(const char& e) { //add to front of list
    addNode(header -> next, e);
}

void LinkedList::addBack(const char& e) { //add to back of list
    addNode(trailer, e);
}

void LinkedList::removeNode(DNode* v) { //remove node v
    DNode* u = v -> prev; //predecessor
    DNode* w = v -> next; //successor
    u -> next = w; //unlink v from list
    w -> prev = u;
    delete v;
}

void LinkedList::removeFront() { //remove from front
    removeNode(header -> next);
}

void LinkedList::removeBack() { //remove from back
    removeNode(trailer -> prev);
}

//functions for Deque class

bool Deque::empty() const { //is deque empty?
    return deq.empty();
}

const char& Deque::front() { //returns front element of deque
    return deq.front();
}

const char& Deque::back() { //returns back element of deque
    return deq.back();
}

int Deque::size()const { //returns size of deque
    return n;
}

void Deque::insertFront(const char& e) { //add to front of deque
    deq.addFront(e);
    n++; //increment size
}

void Deque::insertBack(const char& e) { //add to back of deque
    deq.addBack(e);
    n++; //increment size
}

void Deque::removeFront() { //remove from front
    deq.removeFront();
    n--; //decrement size
}

void Deque::removeBack() { //remove from back
    deq.removeBack();
    n--; //decrement size
}
