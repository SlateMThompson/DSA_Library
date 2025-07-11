#ifndef KEY_VALUE_PAIR_H
#define KEY_VALUE_PAIR_H

#include <ostream>

template<typename T>
class KVpair{
private:

public:
    int key;
    T value;

// Constructors
    KVpair() :
                key{0},
                value{T{}}
    {}

    KVpair(int newKey, T newValue) :
                                    key{newKey},
                                    value{newValue}
    {}

    ~KVpair(){}

    // Operators
    friend std::ostream& operator<<(std::ostream& os, const KVpair<T>& pair) {
        os << "{" << pair.key << ": " << pair.value << "}";
        return os;
    }
};

#endif