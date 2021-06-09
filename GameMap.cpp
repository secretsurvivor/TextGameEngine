//
// Created by 18074751 on 31/10/2019.
//

#include "GameMap.h"
#include <cassert>

#define North(bit) ((bit & 1) == 1) && ((bit & (1 << 4)) == 0)
#define East(bit) ((bit & (1 << 1)) != 0) && ((bit & (1 << 5)) == 0)
#define South(bit) ((bit & (1 << 2)) != 0) && ((bit & (1 << 6)) == 0)
#define West(bit) ((bit & (1 << 3)) != 0) && ((bit & (1 << 7)) == 0)
#define HLocation(pos) pos < size * size && this->map[pos] // Higher
#define LLocation(pos) pos >= 0 && this->map[pos] // Lower

GameMap::Map::Map(uint8_t size) : size(size) {
    map.resize(size*size);
}

GameMap::Map::~Map() {
    this->map.clear();
    this->hConnections.clear();
    this->vConnections.clear();
}

void GameMap::Map::addRoom(int x, int y, Room *room) {
    addRoom(this->position(x, y), room);
}

void GameMap::Map::addRoom(int pos, Room *room) {
    addRoom(pos, room, RoomOptions::AllDirections);
}

void GameMap::Map::addRoom(int x, int y, Room *room, uint8_t options) {
    addRoom(this->position(x, y), room, options);
}

void GameMap::Map::addRoom(int pos, Room *room, uint8_t options)  {
    assert(pos <= size * size && pos >= 0);
    if ( HLocation(pos + size) && North(options)){
        vConnections.insert(pos);
    }
    if (LLocation(pos - size) && South(options)){
        vConnections.insert(pos - size);
    }
    if (HLocation(pos + 1) && East(options)){
        hConnections.insert(pos - (pos / size));
    }
    if (LLocation(pos - 1) && West(options)){
        hConnections.insert((pos - 1) - ((pos - 1) / size));
    }
    this->map[pos] = room;
}

int GameMap::Map::position(int x, int y)  {
    return x + y * size;
}

void GameMap::Map::print()  {
    for (int i = 0; i < (size * size); i++) {
        if (i % size == 0) {
            std::string newLine = "\n";
            wrapOut(&newLine);
        }
        std::string room;
        int pos = (i % size) + size * ((size * size - 1 - i) / size);
        if (this->map[pos] == nullptr) {
            room = "#";
        } else {
            room = std::to_string(this->map[pos]->getID());
        }
        wrapOut(&room);
    }
    wrapEndPara();
}

void GameMap::Map::run() {
    for (auto i = vConnections.begin(); i != vConnections.end(); i++){
        this->map[*i]->setNorth(this->map[*i + size]->getID());
        this->map[*i + size]->setSouth(this->map[*i]->getID());
    }
    for (auto i = hConnections.begin(); i != hConnections.end(); i++){
        int east = *i + (*i/(size - 1));
        this->map[east]->setEast(this->map[east + 1]->getID());
        this->map[east + 1]->setWest(this->map[east]->getID());
    }
}

uint8_t GameMap::RoomOptions::North = 1;
uint8_t GameMap::RoomOptions::East = 1 << 1;
uint8_t GameMap::RoomOptions::South = 1 << 2;
uint8_t GameMap::RoomOptions::West = 1 << 3;
uint8_t GameMap::RoomOptions::AllDirections = North | East | South | West;
uint8_t GameMap::RoomOptions::NotNorth = 1 << 4;
uint8_t GameMap::RoomOptions::NotEast = 1 << 5;
uint8_t GameMap::RoomOptions::NotSouth = 1 << 6;
uint8_t GameMap::RoomOptions::NotWest = 1 << 7;