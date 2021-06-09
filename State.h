//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H

#include "Room.h"
#include <cstdint>

class State {
public:
    explicit State(const uint16_t startRoom);
    void goTo(const uint16_t target);
    void announceLoc() const;
    const Room* getCurrentRoom();
    const uint16_t getCurrentRoomID();
    GameObjects* getInventory();
    void addToInventory(uint16_t _item);
    void removeFromInventory(uint16_t _item);
    void printInventory();

    void setCurrentRoom(uint16_t ID);
    void setInventory(uint16_t objects);
    void clearInventory();
    ~State();
private:
    GameObjects* inventory;
    uint16_t currentRoom;
};


#endif //TEXTADV_STATE_H
