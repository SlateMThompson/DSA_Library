#ifndef QUEUE_H
#define QUEUE_H

#include <memory>

#include "Node.hpp"

template<typename T>
class Queue{
private:
    UniNode<T>* front;
    UniNode<T>* back;
    int queueLength;
    
public:
// Constructors
    Queue() :
                front{nullptr},
                back{nullptr},
                queueLength{0}
    {}
    ~Queue(){

    }

// Accessors
    UniNode<T>* getFront(){return this->front;}
    UniNode<T>* getBack(){return this->back;}
    int getQueueLength(){return this->queueLength;}

    bool isEmpty(){
        if(front == nullptr)
            {return true;}
        else
            {return false;}
    }

    T peek(){
        if (this->isEmpty()){
            throw std::out_of_range("Queue is empty");
        }
        return front->getValue();
    }

// Mutators
    void add(UniNode<T>* newNode) {
    newNode->setNext(nullptr);
    if (isEmpty()) {
        front = back = newNode;
    } else {
        back->setNext(newNode);
        back = newNode;
    }
    queueLength++;
}

    UniNode<T>* take(){
        if(this->isEmpty()){
            throw std::out_of_range("Cannot take as queue is empty");
        }
        UniNode<T>* returnNode = front;
        front = front->getNext();
        queueLength--;
        return returnNode;
    }

    void discard(){delete this->take();}
};

#endif