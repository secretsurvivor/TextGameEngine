//
// Created by 18074751 on 17/10/2019.
//

#ifndef TEXTADV_GAMEOBJECTS_H
#define TEXTADV_GAMEOBJECTS_H

#include <set>
#include "GameObject.h"

class GameObjects{
private:
    std::set<uint16_t> internal;
public:
    GameObjects();
    void add(uint16_t _object);
    void remove(uint16_t _object);
    uint16_t get(std::string* _keyword);
    bool objectPresent(std::string* _keyword);
    std::size_t hashCode();
    int size();
    uint16_t front();
    bool isEmpty();
    void clear();
    std::set<uint16_t>::iterator begin();
    std::set<uint16_t>::iterator end();
};

#endif //TEXTADV_GAMEOBJECTS_H
