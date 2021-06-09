//
// Created by DrMark on 10/2/2017.
//

#include "State.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    Room::rooms[this->currentRoom]->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(const uint16_t startRoom) : currentRoom(startRoom) {
    inventory = new GameObjects();
};

State::~State() {
    delete this->inventory;
}

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(const uint16_t target){
    if (target == 0){
        wrapOut(&badExit);
        wrapEndPara();
    } else {
        this->currentRoom = target;
        this->announceLoc();
    }
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
const Room* State::getCurrentRoom(){
    return Room::rooms[this->currentRoom];
}
const uint16_t State::getCurrentRoomID(){
    return this->currentRoom;
}

GameObjects* State::getInventory() {
    return this->inventory;
}

void State::addToInventory(uint16_t _item) {
    this->inventory->add(_item);
    wrapOut(GameObject::gameobjects[_item]->getKeyword());
    wrapOut(&addedInventory);
    wrapEndPara();
}

void State::removeFromInventory(uint16_t _item) {
    this->inventory->remove(_item);
    wrapOut(&removedInventory1);
    wrapOut(GameObject::gameobjects[_item]->getKeyword());
    wrapOut(&removedInventory2);
    wrapEndPara();
}

void State::printInventory() {
    if (this->inventory->size() > 0) {
        wrapOut(&searchInventory);
        std::string connector = "a";
        if (this->inventory->size() > 1) {
            wrapOut(&connector);
            wrapOut(GameObject::gameobjects[this->inventory->front()]->getKeyword());
            connector = ", a";
            for (auto i = std::next(this->inventory->begin(), 1); i != this->inventory->end(); i++){
                if (i == std::prev(this->inventory->end(), 1)) {
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
            wrapOut(GameObject::gameobjects[this->inventory->front()]->getKeyword());
        }
    } else {
        wrapOut(&emptyInventory);
    }
    wrapEndPara();
}

void State::setCurrentRoom(uint16_t ID) {
    this->currentRoom = ID;
}
void State::clearInventory() {
    this->inventory->clear();
}
void State::setInventory(uint16_t objects) {
    this->inventory->add(objects);
}