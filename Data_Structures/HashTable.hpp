#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

#include "LinkList.hpp"
#include "KVpair.hpp"

template<typename T>
class HashTable{
// Aliases
    using Entry = KVpair<T>;

private:
    int bucketCount;
    LinkList<Entry>* table;
    int(*hashingFunction)(int, HashTable*); // Pointer to hashing function

// function options
    static int defaultHashingFunction(int key, HashTable* currTable) {
        return key % currTable->bucketCount;
    }

public:
// Constructors
    HashTable() :
                    bucketCount{1},
                    hashingFunction(&defaultHashingFunction)
    {
        table = new LinkList<Entry>[bucketCount];
    }
    HashTable(int buckets) : 
                                bucketCount{buckets}, 
                                hashingFunction(defaultHashingFunction)
    {
        table = new LinkList<Entry>[bucketCount];
    }

    ~HashTable(){
        if (table != nullptr) { delete[] table; }
    }

// Accessors
    // Getters  
    int getBucketCount()           const{ return this->bucketCount; }
    LinkList<Entry>* getTable()    const{ return this->table; }

    // Status checks
    bool isEmpty() const{
        for(int i = 0; i < bucketCount; i++){
            if(!(table[i].isEmpty())){
                return false;
            }
        }
        return true;
    }

    const Entry& lookupEntry(int key){
        if (this->isEmpty()){ throw std::logic_error("cannot lookup entry because this Hash Table is empty"); }

        int targetBucketIndex = this->hash(key);
        LinkList<Entry>* targetBucket = &this->table[targetBucketIndex];

        UniNode<Entry>* targetNode = targetBucket->getHead();
        bool entryFound = false;

        while(targetNode != nullptr){
            if((targetNode->getValue()).key == key){
                entryFound = true;
                break;
            } 
            else{
                targetNode = targetNode->getNext();
            }
        }
        
        if(!entryFound){ 
            throw std::logic_error("Entry not found");
        } 
        else{
            return targetNode->getValue(); 
        }
    }

    void printTable(){
        std::cout << "Index\t\tValue\n";
        for(int i = 0; i < this->bucketCount; i++){
            LinkList<Entry>* currList = &this->table[i];
            std::cout << i << "\t\t" << *currList << '\n';
        }
    }

// Mutators
    // Setters
    void setBucketCount(int newBucketCount)                               { this->bucketCount = newBucketCount; }
    void setTable(LinkList<Entry>* newTable)                              { this->table = newTable; }
    void setHashingFunction(int(*newHashingFunction)(int, HashTable*))    { this->hashingFunction = newHashingFunction; }

    void insertEntry(const Entry& newPair){
        int targetBucketIndex = this->hash(newPair.key);
        LinkList<Entry>* targetBucket = &this->table[targetBucketIndex];

        UniNode<Entry>* newNode = new UniNode<Entry>(newPair);

        targetBucket->insertNode(newNode,0);
    }

    UniNode<Entry>* removeEntry(int key){
        if (this->isEmpty()){ throw std::logic_error("cannot remove entry because this Hash Table is empty"); }

        int targetBucketIndex = this->hash(key);
        LinkList<Entry>* targetBucket = &this->table[targetBucketIndex];

        UniNode<Entry>* targetNode = targetBucket->getHead();
        int index = 0;
        bool entryFound = false;

        while(targetNode != nullptr){
            if((targetNode->getValue()).key == key){
                entryFound = true;
                break;
            } else {
                targetNode = targetNode->getNext();
                index++;
            }
        }
        
        if(!entryFound){
            throw std::logic_error("Entry not found");
        } else {
            return targetBucket->removeNode(index);
        }
    }

    int hash(int key){
        return this->hashingFunction(key, this);
    }
};

#endif