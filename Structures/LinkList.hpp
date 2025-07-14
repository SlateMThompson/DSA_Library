/* |---- L i n k L i s t . h p p ---- | */
#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <iostream>
#include "Node.hpp"

template<typename T, int LinkCount>
class LinkList{
// Aliases
    using Node = Node<T, LinkCount>;
    
    private:
    // Member variables
    int listLength;
    Node* head;
    
    public:
    // Constructors
    LinkList(){
        if (LinkCount != 1 && LinkCount != 2) throw std::logic_error("LinkCount must be 1 or 2");
        this->listLength = 0;
        head = nullptr;
    }
    LinkList(int initialListLength){
        Node* traversalNode = new Node(T{});
        Node* buildNode;
        
        for (int i = 0; i < initialListLength; i++){
            buildNode = new Node(T{});
            traversalNode->setNext(buildNode);
            if (LinkCount == 2) buildNode->setPrev(traversalNode);
            traversalNode = buildNode;
        }
        
        this->listLength = initialListLength;
    }
    ~LinkList(){    // destructor
        if(this->isEmpty()) return;
        
        Node* deletionNode = this->head;
        Node* traversalNode = nullptr;
        
        while(deletionNode != nullptr){
            traversalNode = deletionNode->getNext();
            delete deletionNode;
            deletionNode = traversalNode;
        }
    }
    
    // Accessors
    Node* getHead()        { return this->head; }
    int getListLength()    { return this->listLength; }
    
    bool isEmpty(){
        if (head == nullptr || listLength == 0)
            return true;
        else
            return false;
    }
    
    Node* getNode(int index){
        if (0 > index || index >= listLength || head == nullptr) throw std::out_of_range("index out of range");

        Node* traversalNode = head;
        for (int i = 0; i < index; i++){
            traversalNode = traversalNode->getNext();
        }

        return traversalNode;
    }

    int indexOf(Node* targetNode){
        Node* traversalNode = head;
        int index = 0;
        while (traversalNode != nullptr){
            if (targetNode == traversalNode) return index;
            if (index > listLength) return -1;
            traversalNode = traversalNode->getNext();
            index++;
        }
    }

// Mutators
    void setListLength(int newListLength)    { this->listLength = newListLength; }
    void setHead(Node* newHead)              { this->head = newHead; }

    void insert(int index, Node* newNode){
        if (0 > index || index > listLength) throw std::out_of_range("index out of range");
        
        newNode->unconnect();
        
        if (index == 0){ 
            if (head != nullptr){
                newNode->setNext(head);
                if (LinkCount < 2)
                    head->setPrev(newNode);
            }
            head = newNode;

        } else if (index == listLength){
            Node* prevNode = head;
            for (int i = 0; i < index; i++) prevNode = prevNode->getNext();
            prevNode->setNext(newNode);
            if (LinkCount == 2) newNode->setPrev(prevNode);

        } else {
            Node* prevNode = head;
            Node* nextNode;

            for (int i = 0; i < index; i++) prevNode = prevNode->getNext();
            nextNode = prevNode->getNext();

            prevNode->setNext(newNode);
            newNode->setNext(nextNode);
            if (LinkCount == 2){
                nextNode->setPrev(newNode);
                newNode->setPrev(prevNode);
            } 
        }

        listLength++;
        return;
    }

    Node* remove(int index){
        if (0 > index || index >= listLength) throw std::out_of_range("index out of range");
        Node* targetNode = head;

        if (index == 0){
            head = head->getNext();
            if (LinkCount == 2 && head != nullptr) 
                head->setPrev(nullptr);

        }
        else if (index == listLength-1){
            Node* prevNode = head;
            for (int i = 0; i < index-1; i++) prevNode = prevNode->getNext(); 
            targetNode = prevNode->getNext();
            prevNode->setNext(nullptr);

        } else{
            Node* prevNode = head;
            Node* nextNode;
            for (int i = 0; i < index; i++) prevNode = prevNode->getNext();
            targetNode = prevNode->getNext();
            nextNode = targetNode->getNext();

            prevNode->setNext(nextNode);
            if (LinkCount == 2) nextNode->setPrev(prevNode);

        }

        listLength--;
        targetNode->unconnect();
        return targetNode;
    }

// Operators
    bool operator == (const LinkList& node) {
        if (this == &node)
            return true;
        else
            return false;
    }

    LinkList& operator = (LinkList& source) {
        if (this == &source) return *this;            // self assignment check
        while (!this->isEmpty()) delete remove(0);    // clears left-hand-side list
        if (source.isEmpty()) return *this;           // returns blank list if source is empty

        Node* sourceScanner = source.head;

        head = new Node(sourceScanner->getData());
        Node* traversalNode = this->head;
        Node* buildNode;

        while (sourceScanner != nullptr) {
            buildNode = new Node(sourceScanner->getData());
            traversalNode->setNext(buildNode);
            buildNode->setPrev(traversalNode);
            traversalNode = buildNode;
            sourceScanner = sourceScanner->getNext();
        }

        listLength = source.listLength;
        return *this;
    }

    LinkList& operator += (Node* other) { // appends a node to the end of the list
        this->insert(listLength, other);
        return *this;
    }

    friend std::ostream& operator << (std::ostream& os, LinkList& list) {
        for (int i = 0; i < list.listLength; i++) {
            os << *(list.getNode(i));
            if (i < list.listLength - 1) os << ", ";
        }
        return os;
    }

};

#endif