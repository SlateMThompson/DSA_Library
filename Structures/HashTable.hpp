#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>

#include "LinkList.hpp"
#include "KVpair.hpp"

template<typename T>
class HashTable{
// Aliases
    using KVpair = KVpair<T>;
    using Node = Node<KVpair, 2>;

private:
    uint32_t bucketCount;
    LinkList<KVpair, 2>* table;
    int(*hashingFunction)(int, HashTable*); // Pointer to hashing function

// function options
    static int defaultHashingFunction(int key, HashTable* currTable) {
        return key % currTable->bucketCount;
    }

public:
// Constructors
    HashTable() :
                    bucketCount{0},
                    hashingFunction(&defaultHashingFunction)
    {
        table = new LinkList<KVpair, 2>[bucketCount];
    }
    HashTable(uint32_t buckets) : 
                                bucketCount{buckets}, 
                                hashingFunction(&defaultHashingFunction)
    {
        table = new LinkList<KVpair, 2>[bucketCount];
    }

    ~HashTable(){
        if (table != nullptr) { delete[] table; }
    }

// Accessors
    // Getters  
    int getBucketCount()           const{ return this->bucketCount; }
    LinkList<KVpair, 2>* getTable()    const{ return this->table; }

    // Status checks
    bool isEmpty() const{
        for(int i = 0; i < bucketCount; i++){
            if(!(table[i].isEmpty())){
                return false;
            }
        }
        return true;
    }

    const KVpair& lookup(int key){
        if (this->isEmpty()){ throw std::logic_error("cannot lookup KVpair because this Hash Table is empty"); }

        int targetBucketIndex = this->hash(key);
        LinkList<KVpair, 2>* targetBucket = &this->table[targetBucketIndex];

        Node* targetNode = targetBucket->getHead();
        bool KVpairFound = false;

        while(targetNode != nullptr){
            if((targetNode->getData()).key == key){
                KVpairFound = true;
                break;
            } 
            else{
                targetNode = targetNode->getNext();
            }
        }
        
        if(!KVpairFound){ 
            throw std::logic_error("KVpair not found");
        } 
        else{
            return targetNode->getData(); 
        }
    }

    void printTable(){
        std::cout << "Index\t\tValue\n";
        for(int i = 0; i < this->bucketCount; i++){
            LinkList<KVpair, 2>* currList = &this->table[i];
            std::cout << i << "\t\t" << *currList << '\n';
        }
    }

// Mutators
    // Setters
    void setBucketCount(int newBucketCount)                               { this->bucketCount = newBucketCount; }
    void setTable(LinkList<KVpair, 2>* newTable)                              { this->table = newTable; }
    void setHashingFunction(int(*newHashingFunction)(int, HashTable*))    { this->hashingFunction = newHashingFunction; }

    void insert(const KVpair& newPair){
        int targetBucketIndex = this->hash(newPair.key);
        LinkList<KVpair, 2>* targetBucket = &this->table[targetBucketIndex];

        Node* newNode = new Node(newPair);

        targetBucket->insert(0, newNode);
    }

    Node* remove(int key){
        if (this->isEmpty()){ throw std::logic_error("cannot remove KVpair because this Hash Table is empty"); }

        int targetBucketIndex = this->hash(key);
        LinkList<KVpair, 2>* targetBucket = &this->table[targetBucketIndex];

        Node* targetNode = targetBucket->getHead();
        int index = 0;
        bool KVpairFound = false;

        while(targetNode != nullptr){
            if((targetNode->getData()).key == key){
                KVpairFound = true;
                break;
            } else {
                targetNode = targetNode->getNext();
                index++;
            }
        }
        
        if(KVpairFound == false) throw std::logic_error("KVpair not found");
        return targetBucket->remove(0);
    }

    int hash(int key){
        return this->hashingFunction(key, this);
    }
};

#endif