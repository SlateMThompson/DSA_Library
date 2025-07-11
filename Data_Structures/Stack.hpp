#ifndef STACK_H
#define STACK_H

#include "Node.hpp"

template<typename T>
class Stack{
private:
    UniNode<T>* top;
    int stackLength;
    
public:
// Constructors
    Stack() :
            top{nullptr},
            stackLength{0}
    {}

    ~Stack(){
        if(this->isEmpty()){return;}

        UniNode<T>* deletionNode = this->top;
        UniNode<T>* traversalNode = deletionNode->getNext();
        
        for(int i = 0; i < this->stackLength; i++){
            delete deletionNode;
            deletionNode = traversalNode;
            traversalNode = traversalNode->getNext();
        }
    }
// Operators
    Stack<T>& operator += (UniNode<T>* appendingNode){
        appendingNode->setNext(this->top);
        this->top = appendingNode;
        return this;
    }

// Accessors
    int getStackLength(){return this->stackLength;}
    UniNode<T>* getTop(){return this->top;}

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
            return top->getValue();
        }
    }

// Mutators
    void push(T value){
        UniNode<T>* buildPtr = new UniNode<T>(value);
        buildPtr->setNext(this->top);

        this->top = buildPtr;
        this->stackLength++;
    }

    UniNode<T>* pop(){
        if(this->isEmpty()){
            throw std::out_of_range("Stack is empty");
        }
        UniNode<T>* returnNode = top;

        this->top = top->getNext();
        this->stackLength++;
        return returnNode;
    }

    void discard(){
        delete pop();
    }
};

#endif