//
// Created by 18074751 on 17/10/2019.
//

#include "GameObject.h"
;

GameObject::GameObject(const uint16_t _ID, const std::string* _name, const std::string* _desc, const std::string* _key) : ID(_ID), name(_name), description(_desc), keyword(_key) {}

const uint16_t GameObject::getID() {
    return this->ID;
}

const std::string* GameObject::getName(){
    return this->name;
}

const std::string* GameObject::getDesc(){
    return this->description;
}

const std::string* GameObject::getKeyword() {
    return this->keyword;
}

void GameObject::inspect() {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
}
std::size_t GameObject::hashCode() {
    return std::hash<std::string>{}(*this->keyword);
}

std::unordered_map<uint16_t, GameObject*> GameObject::gameobjects;
GameObject* GameObject::addGameObject(GameObject *obj) {
    gameobjects[obj->getID()] = obj;
    return obj;
}