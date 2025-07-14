#ifndef STACK_H
#define STACK_H

#include "Node.hpp"

template<typename T>
class Stack{
    using Node = Node<T, 1>;

private:
    Node* top;
    int stackLength;
    
public:
// Constructors
    Stack() :
            top{nullptr},
            stackLength{0}
    {}

    ~Stack(){
        if(this->isEmpty()){return;}

        Node* deletionNode = this->top;
        Node* traversalNode = deletionNode->getNext();
        
        for(int i = 0; i < this->stackLength; i++){
            delete deletionNode;
            deletionNode = traversalNode;
            traversalNode = traversalNode->getNext();
        }
    }
    
    // Accessors
    int getStackLength(){return this->stackLength;}
    Node* getTop(){return this->top;}
    
    bool isEmpty(){
        if(top == nullptr)
        {return true;} 
        else
        {return false;}
    }
    
    T peek(){
        if(this->isEmpty()){
            throw std::out_of_range("Stack is empty");
        } else {
            return top->getData();
        }
    }
    
    // Mutators
    void push(T value){
        Node* newNode = new Node(value);
        newNode->setNext(this->top);
        
        this->top = newNode;
        this->stackLength++;
    }

    void pushNode(Node* newNode){
        newNode->setNext(this->top);
        
        this->top = newNode;
        this->stackLength++;
    }
    
    Node* pop(){
        if(this->isEmpty()){
            throw std::out_of_range("Stack is empty");
        }
        Node* returnNode = top;
        
        this->top = top->getNext();
        this->stackLength++;
        return returnNode;
    }
    
    void discard(){
        delete pop();
    }

    // Operators
    Stack<T>& operator += (Node* appendingNode){
        appendingNode->setNext(this->top);
        this->top = appendingNode;
        return this;
    }
};

#endif