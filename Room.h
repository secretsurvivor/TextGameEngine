//
// Created by DrMark on 10/2/2017.
//

#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include <string>
#include <forward_list>
#include <list>
#include <unordered_map>
#include "GameObjects.h"

class Room {
private:
    const uint16_t ID;
    const std::string* name;
    const std::string* description;
    std::size_t hash;
    uint16_t north;
    uint16_t east;
    uint16_t south;
    uint16_t west;

    GameObjects* objects;
public:
    uint16_t getID();
    std::string* getName();
    std::string* getDescription();
    Room(const uint16_t ID, const std::string *_name, const std::string *_desc);
    ~Room();
    void describe() const;
    static std::unordered_map<uint16_t, Room*> rooms;
    static Room* addRoom(Room* room);
    static void hashRooms();
    uint16_t getNorth() const;
    uint16_t getEast() const;
    uint16_t getSouth() const;
    uint16_t getWest() const;
    void setNorth(uint16_t _north);
    void setEast(uint16_t _east);
    void setSouth(uint16_t _south);
    void setWest(uint16_t _west);
    GameObjects* getObjects() const;
    void printItems() const;
    bool hasItems() const;
    void addItem(uint16_t item) const;
    void removeItem(uint16_t item) const;
    void setHash(std::size_t hash);
    std::size_t getHash();
};

#endif //TEXTADV_ROOM_H
