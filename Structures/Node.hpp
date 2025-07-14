/* |---- N o d e . h p p ---- | */
#ifndef NODE_HPP
#define NODE_HPP

#include <ostream>

#define NEXT_LINK 0
#define PREV_LINK 1

template<typename T, unsigned int LinkCount>
class Node{
private:
// Member variables
    T data;
    Node* links[LinkCount];

public:
// Constructors
    Node() : data{T{}}{
        for (int i = 0; i < LinkCount; i++){
            this->links[i] = nullptr;
        }
    }
    Node(T initialData) : data{initialData}{
        for (int i = 0; i < LinkCount; i++){
            this->links[i] = nullptr;
        }
    }
    Node(Node* initialNext){
        if (LinkCount < 1) throw std::logic_error("Invalid Construtor: LinkCount is less than 1");

        this->links[NEXT_LINK] = initialNext;
        for(int i = 1; i < LinkCount; i++){
            this->links[i] = nullptr;
        }
    }
    Node(Node* initialNext, Node* initialPrev){
        if (LinkCount < 2) throw std::logic_error("Invalid Construtor: LinkCount is less than 1");

        this->links[NEXT_LINK] = initialNext;
        this->links[PREV_LINK] = initialPrev;
        for(int i = 2; i < LinkCount; i++){
            this->links[i] = nullptr;
        }
    }
    Node(T initialData, Node* initialNext) : data{initialData}{
        if (LinkCount < 1) throw std::logic_error("Invalid Constructor: LinkCount is less than 1.");

        this->links[NEXT_LINK] = initialNext;
        for(int i = 1; i < LinkCount; i++){
            this->links[i] = nullptr;
        }
    }
    Node(T initialData, Node* initialNext, Node* initialPrev) : data{initialData}{
        if (LinkCount < 2) throw std::logic_error("Invalid Constructor: LinkCount is less than 1.");

        this->links[NEXT_LINK] = initialNext;
        this->links[PREV_LINK] = initialPrev;
        for(int i = 2; i < LinkCount; i++){
            this->links[i] = nullptr;
        }
    }
    ~Node(){} // destructor

// Accessor functions
    T& getData()          { return this->data; }
    const T& getData()    const{ return this->data; } // Overload

    int getLinkCount()    { return LinkCount; }
    

    Node* getNext(){
        if (LinkCount < 1) 
            throw std::logic_error("This function is not available for Nodes with less than one link");
        else
            return this->links[NEXT_LINK];
    }

    Node* getPrev()             {
        if (LinkCount < 2)
            throw std::logic_error("This function is not available for Nodes with less than two links");
        else
            return this->links[PREV_LINK];
    }

    Node* getLink(int index)    {
        if (0 > index || index >= LinkCount) throw std::out_of_range("index for setLink is out of range of LinkCount");
        return this->links[index];
    }

// Mutators functions
    void setData(T newData)    { this->data = newData; }

    void setNext(Node* newNext){
        if (LinkCount < 1)
            throw std::logic_error("This function is not available for Nodes with less than two links");
        else
            this->links[NEXT_LINK] = newNext;
    }

    void setPrev(Node* newPrev){
        if (LinkCount < 2)
            throw std::logic_error("This function is not available for Nodes with less than two links");
        else
            this->links[PREV_LINK] = newPrev;
    }

    void setLink(int index, Node* newLink){
        if (0 > index || index >= LinkCount) throw std::out_of_range("index for setLink is out of range of LinkCount");
        this->links[index] = newLink;
    }
    
    void unconnect(){
        for (int i = 0; i < LinkCount; i++){
            this->links[i] = nullptr;
        }
    }

// Operators
    Node& operator = (const Node& node){
        if (this != &node) {
            data = node.data;
            for (int i = 0; i < LinkCount; ++i)
                links[i] = node.links[i];
        }
        return *this;
    }

    bool operator == (const Node& node) const {
        if (this == &node)
            return true;
        else
            return false;
    }

    friend std::ostream& operator << (std::ostream& os, const Node& node) {
        os << node.getData();
        return os;
    }
};
#endif