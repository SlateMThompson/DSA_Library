#ifndef NODE_H
#define NODE_H

#include <memory>

template<typename T>
class BiNode{
private:
    T value;
    BiNode* next; 
    BiNode* prev;

public:
// Constructors
    BiNode() :
                  value{T{}},
                  next{nullptr},
                  prev{nullptr}
    {}
    BiNode(T value) : 
                         value{value},
                         next{nullptr},
                         prev{nullptr}
    {}
    BiNode(BiNode* next, BiNode* prev) :
                                            value{T{}},
                                            next{next},
                                            prev{prev}
    {}
    BiNode(T value, BiNode* next, BiNode* prev) : 
                                                     value{value},
                                                     next{next},
                                                     prev{prev}
    {}
    ~BiNode(){}

    friend std::ostream& operator << (std::ostream& os, BiNode& node) {
        os << node.value;
        return os;
    }
    
// Accessor functions
    // Getters
    const T& getValue()        const { return this->value; }
    BiNode* getNext()    const { return this->next; }
    BiNode* getPrev()    const { return this->prev; }

// Mutator functions
    // Setters
    void setValue(T newValue)     { this->value = newValue; }
    void setNext(BiNode* node)    { this->next = node; }
    void setPrev(BiNode* node)    { this->prev = node; }

    void unlink(){ 
        next = nullptr;
        prev = nullptr;
    }
};

template<typename T>
class UniNode{
private:
    T value;
    UniNode* next; 
    
public:
    // Constructors
    UniNode() : 
                   value{},
                   next{nullptr}
    {}
    UniNode(T value) : 
                          value{value}, 
                          next{nullptr}
    {}
    UniNode(UniNode* next) : 
                                value{T{}},
                                next{next}
    {}
    UniNode(T value, UniNode* next) : 
                                         value{value},
                                         next{next} 
    {}
    ~UniNode(){}

// Operators
    friend std::ostream& operator << (std::ostream& os, UniNode& node) {
        os << node.getValue();
        return os;
    }

// Access functions
    // Getters
    const T& getValue()         const { return value; }
    UniNode* getNext()    const { return this->next; }

// Mutator functions
    // Setters
    void setValue(T newValue)      { this->value = newValue; }
    void setNext(UniNode* node)    { this->next = node; }

    void unlink(){
        this->next = nullptr;
    }
};

#endif