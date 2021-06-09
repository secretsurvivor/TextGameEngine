//
// Created by DrMark on 10/2/2017.
//

#include <cstdint>
#include "Room.h"

Room::Room(const uint16_t ID, const std::string* _name, const std::string *_desc) :
    ID(ID), name(_name), description(_desc), north(), east(), west(), south(), objects() {
    objects = new GameObjects();
};

Room::~Room() {
    delete this->name;
    delete this->description;
    delete this->objects;
}

///////////// Variable Getters /////////////
uint16_t Room::getID() {
    return this->ID;
}
std::string* Room::getName() {
    return (std::string*)this->name;
}
std::string* Room::getDescription() {
    return (std::string*)this->description;
}

void Room::describe() const {
    wrapEndPara();
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    this->printItems();
}

///////////// Global Room Hash Table /////////////
std::unordered_map<uint16_t, Room*> Room::rooms;
Room* Room::addRoom(Room* room) {
    Room::rooms[room->getID()] = room;
    return room;
}

void Room::hashRooms() {
    for (std::pair<uint16_t, Room*> element : Room::rooms){
        element.second->setHash(element.second->getObjects()->hashCode());
    }
}

///////////// Direction Methods /////////////
uint16_t Room::getNorth() const { // North
    return this->north;
}
void Room::setNorth(uint16_t _north) {
    this->north = _north;
}

uint16_t Room::getEast() const { // East
    return this->east;
}
void Room::setEast(uint16_t _east) {
    this->east = _east;
}

uint16_t Room::getSouth() const { // South
    return this->south;
}
void Room::setSouth(uint16_t _south) {
    this->south = _south;
}

uint16_t Room::getWest() const { // West
    return this->west;
}
void Room::setWest(uint16_t _west) {
    this->west = _west;
}

///////////// Object Access /////////////
GameObjects* Room::getObjects() const {
    return this->objects;
}

bool Room::hasItems() const {
    return this->objects->isEmpty();
}

void Room::addItem(uint16_t item) const {
    this->objects->add(item);
}

void Room::removeItem(uint16_t item) const {
    this->objects->remove(item);
}

void Room::printItems() const {
    if (this->objects->size() > 0) {
        wrapOut(&findItems);
        std::string connector = "a";
        if (this->objects->size() > 1) {
            wrapOut(&connector);
            wrapOut(GameObject::gameobjects[this->objects->front()]->getKeyword());
            connector = ", a";
            for (auto i = std::next(this->getObjects()->begin(), 1); i != this->getObjects()->end(); i++){
                if (i == std::prev(this->getObjects()->end(), 1)) {
                    connector = "and a";
                    wrapOut(&connector);
                    wrapOut(GameObject::gameobjects[*i]->getKeyword());
                } else {
                    wrapOut(&connector);
                    wrapOut(GameObject::gameobjects[*i]->getKeyword());
                }
            }
        } else {
            wrapOut(&connector);
            wrapOut(GameObject::gameobjects[this->objects->front()]->getKeyword());
        }
    } else {
        wrapOut(&noItems);
    }
    wrapEndPara();
}

void Room::setHash(std::size_t hash) {
    this->hash = hash;
}

std::size_t Room::getHash() {
    return this->hash;
}