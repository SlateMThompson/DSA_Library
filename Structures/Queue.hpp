#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include "Node.hpp"

template<typename T>
class Queue{
    using Node = Node<T, 1>;

private:
    Node* front;
    Node* back;
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
    Node* getFront()    {return this->front;}
    Node* getBack()     {return this->back;}
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
        return front->getData();
    }

// Mutators
    void add(int initialData) {
        Node* newNode = new Node(initialData);

        newNode->setNext(nullptr);
        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->setNext(newNode);
            back = newNode;
        }
        queueLength++;
    }

    void addNode(Node* newNode) {
        newNode->setNext(nullptr);
        if (isEmpty()) {
            front = back = newNode;
        } else {
            back->setNext(newNode);
            back = newNode;
        }
        queueLength++;
    }

    Node* take(){
        if(this->isEmpty()){
            throw std::out_of_range("Cannot take as queue is empty");
        }
        Node* returnNode = front;
        front = front->getNext();
        queueLength--;
        return returnNode;
    }

    void discard(){delete this->take();}
};

#endif