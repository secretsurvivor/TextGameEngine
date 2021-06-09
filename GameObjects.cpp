//
// Created by 18074751 on 17/10/2019.
//

#include "GameObjects.h"
#include "Room.h"
#include <cstring>

GameObjects::GameObjects() : internal() {}

void GameObjects::add(uint16_t _object) {
    if (_object > 0) {
        this->internal.insert(_object);
    }
}

void GameObjects::remove(uint16_t _object) {
    this->internal.erase(_object);
}

uint16_t GameObjects::get(std::string *_keyword) {
    if (!this->internal.empty()){
        for (uint16_t obj : this->internal){
            if (*GameObject::gameobjects[obj]->getKeyword() == *_keyword){
                return obj;
            }
        }
    }
    return 0;
}

bool GameObjects::objectPresent(std::string *_keyword) {
    return this->get(_keyword) > 0;
}

std::size_t GameObjects::hashCode() {
    std::string rtn;
    for (uint16_t obj : this->internal){
        rtn = rtn + *GameObject::gameobjects[obj]->getKeyword();
    }
    return std::hash<std::string>{}(rtn);
}

int GameObjects::size(){
    return this->internal.size();
}
uint16_t GameObjects::front() {
    return *this->internal.begin();
}
bool GameObjects::isEmpty() {
    return this->internal.empty();
}
void GameObjects::clear() {
    this->internal.clear();
}
std::set<uint16_t>::iterator GameObjects::begin() {
    return this->internal.begin();
}
std::set<uint16_t>::iterator GameObjects::end() {
    return this->internal.end();
}