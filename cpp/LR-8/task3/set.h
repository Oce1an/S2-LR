#ifndef SET_H
#define SET_H

#include "map.h"

template<typename KeyType>
class Set : public Map<KeyType, char> {
public:
    bool insert(const KeyType& key) {
        return Map<KeyType, char>::insert(key, '\0');
    }
    // скрываем оператор [] и at (они не нужны)
    void operator[](const KeyType&) = delete;
};
#endif