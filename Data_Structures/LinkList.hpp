#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include "Node.hpp"

template<typename T>
class LinkList{
private:
    int listLength;
    UniNode<T>* head;
    
public:
// Constructors
    LinkList() :
                head{nullptr},
                listLength{0}
    {}

    LinkList(int listLength){
        if(listLength < 1){
            this->head = nullptr;
            this->listLength = listLength;
            return;
        }
        this->listLength = listLength;

        this->head = new UniNode<T>(T{});
        UniNode<T>* traversalPtr = this->head;

        for(int i = 1; i < listLength; i++) {
            UniNode<T>* buildPtr = new UniNode<T>(T{});
            traversalPtr->setNext(buildPtr);
            traversalPtr = buildPtr;
        }
    }

    LinkList(T* array, int arrayLength){
        this->listLength = arrayLength;

        this->head = new UniNode<T>(array[0]);
        UniNode<T>* traversalPtr = this->head;

        for(int i = 1; i < arrayLength; i++){
            UniNode<T>* buildPtr = new UniNode<T>(array[i]);
            traversalPtr->setNext(buildPtr);
            traversalPtr = buildPtr;
        }
    }

    ~LinkList(){
        if(this->isEmpty()){
            return;
        }
        UniNode<T>* deletionNode = this->head;
        UniNode<T>* traversalNode = nullptr;

        while(deletionNode != nullptr){
            traversalNode = deletionNode->getNext();
            delete deletionNode;
            deletionNode = traversalNode;
        }
    }

// Operators
    LinkList<T>& operator = (const LinkList<T>& newList) {
        if (this == &newList) return *this; // Self-assignment check

        while (!this->isEmpty()) {
            deleteNode(0);
        }

        if (newList.head == nullptr) {
            this->head = nullptr;
            this->listLength = 0;
            return *this;
        }

        this->head = new UniNode<T>(newList.head->getValue());
        UniNode<T>* curr = this->head;
        UniNode<T>* newListCurr = newList.head->getNext();

        while (newListCurr != nullptr) {
            UniNode<T>* newNode = new UniNode<T>(newListCurr->getValue());
            curr->setNext(newNode);
            curr = newNode;
            newListCurr = newListCurr->getNext();
        }

        this->listLength = newList.listLength;
        return *this;
    }

    LinkList<T>& operator += (UniNode<T>* appendingNode){
        // Appends a node to the end of the list
        this->insertNode(appendingNode, this->listLength);
        return *this;
    }

    friend std::ostream& operator << (std::ostream& os, LinkList& list) {
        for (int i = 0; i < list.listLength; i++){
            os << *(list.getNodeAt(i)) << ", ";
        }
        return os;
    }

// Accessors
    int getListLength(){return this->listLength;}

    UniNode<T>* getHead(){return this->head;}

    bool isEmpty(){
        if(this->head == nullptr && this->listLength == 0)
            {return true;}
        else
            {return false;}
    }

    UniNode<T>* getNodeAt(int index){
        //Returns pointer to Node at given index
        if(index < 0 || index >= this->listLength || this->head == nullptr){return nullptr;}

        UniNode<T>* traversalPtr = this->head;
        for(int i = 0; i < index; i++){
            traversalPtr = traversalPtr->getNext();
        }
        return traversalPtr;
    }

    T getValueAt(int index){
        // Returns value in Node at given indexc
        if(index < 0 || index >= this->listLength){
            throw std::out_of_range("Index out of bounds");
        }

        UniNode<T>* traversalPtr = this->head;
        for(int i = 0; i < index; i++){
            traversalPtr = traversalPtr->getNext();
        }
        return traversalPtr->getValue();
    }

    int getIndexOf(UniNode<T>* targetNode){
        // Returns index of given Node. Returns -1 if Node is not found
        int index = 0;
        UniNode<T>* traversalPtr = this->head;

        while(traversalPtr != nullptr){
            if(traversalPtr == targetNode){
                return index;
            }
            traversalPtr = traversalPtr->getNext();
            index++;
        }
        return -1;
    }

    void printList(){
        if(this->isEmpty()){
            std::cout << "List is empty.\n";
            return;
        }
        UniNode<T>* traversalPtr = this->getNodeAt(0);

        std::cout << "Index\t\tValue\n";
        try{
            for(int i = 0; i < this->listLength; i++){
                std::cout << i << "\t\t" << traversalPtr->getValue() << '\n';
                traversalPtr = traversalPtr->getNext();
            }
        }
        catch(const std::exception& e){
            std::cout << "List could not be printed.\n";
        }
    }

// Mutators
    void setListLength(int newListLength){
        this->listLength = newListLength;
    }
    void setHead(UniNode<T>* newHead){
        this->head = newHead;
    }

    void insertNode(UniNode<T>* newNode, int index){
        if(index < 0 || index > this->listLength) return;
        if(index == 0){
            newNode->setNext(head);
            this->head = newNode;
            this->listLength++;
            return;
        }
        UniNode<T>* previousNode = getNodeAt(index-1);
        if(previousNode == nullptr) return;
        UniNode<T>* followingNode = previousNode->getNext();

        previousNode->setNext(newNode);
        newNode->setNext(followingNode);

        this->listLength++;
    }

    UniNode<T>* removeNode(int index){
        if(index < 0 || index >= this->listLength) {
            throw std::out_of_range("index is out of bounds");
        }
        if(index == 0){
            UniNode<T>* targetNode = head;
            this->head = head->getNext();
            this->listLength--;
            return targetNode;
        }
        UniNode<T>* previousNode = getNodeAt(index-1);
        UniNode<T>* targetNode = previousNode->getNext();

        previousNode->setNext(targetNode->getNext());
        targetNode->unlink();
        this->listLength--;

        return targetNode;
    }

    void deleteNode(int index){
        delete removeNode(index);
    }

    void moveNode(int launchIndex, int targetIndex){
        insertNode(removeNode(launchIndex), targetIndex);
    }
};


template<typename T>
class BiLinkList{
private:
    int listLength;
    BiNode<T>* head;

public:
// Constructors
    BiLinkList() :
                head{nullptr},
                listLength{0}
    {}

    BiLinkList(int listLength){
        if(listLength<1){
            this->head = nullptr;
            this->listLength = listLength;
            return;
        }
        this->listLength = listLength;

        this->head = new BiNode<T>(T{});
        BiNode<T>* traversalPtr = this->head;

        for(int i = 1; i < listLength; i++) {
            BiNode<T>* buildPtr = new BiNode(T());
            traversalPtr->setNext(buildPtr);
            buildPtr->setPrev(traversalPtr);
            traversalPtr = buildPtr;
        }
    }

    BiLinkList(T* array, int arrayLength){
        this->listLength = arrayLength;

        this->head = new BiNode<T>(array[0]);
        BiNode<T>* traversalPtr = this->head;

        for(int i = 1; i < arrayLength; i++) {
            BiNode<T>* buildPtr = new BiNode(array[i]);
            traversalPtr->setNext(buildPtr);
            buildPtr->setPrev(traversalPtr);
            traversalPtr = buildPtr;
        }
    }

    ~BiLinkList(){
        if(this->isEmpty()){
            return;
        }
        while (!this->isEmpty()) {
            deleteNode(0);
        }
    }

// Operators
    BiLinkList<T>& operator = (const BiLinkList<T>& newList) {
        if (this == &newList) return *this; // Self-assignment check

        while (!this->isEmpty()) {
            deleteNode(0);
        }

        if (newList.head == nullptr) {
            this->head = nullptr;
            this->listLength = 0;
            return *this;
        }

        this->head = new BiNode<T>(newList.head->getValue());
        BiNode<T>* curr = this->head;
        BiNode<T>* newListCurr = newList.head->getNext();

        while (newListCurr != nullptr) {
            BiNode<T>* newNode = new BiNode<T>(newListCurr->getValue());
            curr->setNext(newNode);
            newNode->setPrev(curr);
            curr = newNode;
            newListCurr = newListCurr->getNext();
        }

        this->listLength = newList.listLength;
        return *this;
    }

    BiLinkList<T>& operator += (const BiNode<T>& appendingNode){
        // Appends a node to the end of the list
        this->insertNode(appendingNode, this->listLength);
        return *this;
    }

    friend std::ostream& operator << (std::ostream& os, BiLinkList& list) {
        for (int i = 0; i < list.listLength; i++){
            os << list.getNodeAt(i) << ", ";
        }
        return os;
    }

// Accessors
    int getListLength(){return this->listLength;}

    BiNode<T>* getHead(){return this->head;}

    bool isEmpty(){
        if(this->head == nullptr && this->listLength == 0)
            {return true;}
        else
            {return false;}
        
    }

    BiNode<T>* getNodeAt(int index){
        //Returns pointer to Node at given index
        if(index < 0 || index >= this->listLength || this->head == nullptr){return nullptr;}

        BiNode<T>* traversalPtr = this->head;
        for(int i = 0; i < index; i++){
            traversalPtr = traversalPtr->getNext();
        }
        return traversalPtr;
    }

    T getValueAt(int index){
        // Returns value in Node at given indexc
        if(index < 0 || index >= this->listLength){
            throw std::out_of_range("Index out of bounds");
        }

        BiNode<T>* traversalPtr = this->head;
        for(int i = 0; i < index; i++){
            traversalPtr = traversalPtr->getNext();
        }
        return traversalPtr->getValue();
    }

    int getIndexOf(BiNode<T>* targetNode){
        // Returns index of given Node. Returns -1 if Node is not found
        int index = 0;
        BiNode<T>* traversalPtr = this->head;

        while(traversalPtr != nullptr){
            if(traversalPtr == targetNode){
                return index;
            }
            traversalPtr = traversalPtr->getNext();
            index++;
        }
        return -1;
    }

    void printList(){
        if(this->head == nullptr || this->listLength == 0){
            std::cout << "List is empty.\n";
            return;
        }
        BiNode<T>* traversalPtr = this->getNodeAt(0);

        std::cout << "Index\t\tValue\n";
        try{
            for(int i = 0; i < this->listLength; i++){
                std::cout << i << "\t\t" << traversalPtr->getValue() << '\n';
                traversalPtr = traversalPtr->getNext();
            }
        }
        catch(const std::exception& e){
            std::cout << "List could not be printed.\n";
        }
    }

// Mutators
    void setListLength(int newListLength){
        this->listLength = newListLength;
    }
    void setHead(BiNode<T>* newHead){
        this->head = newHead;
    }

    void insertNode(BiNode<T>* newNode, int index){
        if(index < 0 || index > this->listLength) {
            throw std::out_of_range("index is out of bounds");
        }
        if(index == 0){
            newNode->setNext(head);
            this->head = newNode;
            this->listLength++;
            return;
        }
        BiNode<T>* previousNode = getNodeAt(index-1);
        if(previousNode == nullptr) return;
        BiNode<T>* followingNode = previousNode->getNext();

        previousNode->setNext(newNode);
        newNode->setNext(followingNode);

        this->listLength++;
    }

    BiNode<T>* removeNode(int index){
        if(index < 0 || index >= this->listLength) {
            throw std::out_of_range("index is out of bounds");
        }
        if(index == 0){
            BiNode<T>* targetNode = head;
            this->head = head->getNext();
            this->listLength--;
            return targetNode;
        }
        BiNode<T>* previousNode = getNodeAt(index-1);
        BiNode<T>* targetNode = previousNode->getNext();

        previousNode->setNext(targetNode->getNext());
        targetNode->unlink();
        this->listLength--;

        return targetNode;
    }

    void deleteNode(int index){
        delete removeNode(index);
    }

    void moveNode(int launchIndex, int targetIndex){
        insertNode(removeNode(launchIndex), targetIndex);
    }
};

#endif