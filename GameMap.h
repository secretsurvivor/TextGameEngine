//
// Created by 18074751 on 31/10/2019.
//

#ifndef TEXTADV_GAMEMAP_H
#define TEXTADV_GAMEMAP_H

#include <cstdint>
#include <unordered_set>
#include <vector>
#include "Room.h"

namespace GameMap {
    class Map {
    private:
        std::vector<Room*> map;
        std::unordered_set<uint16_t > vConnections; //size * (size - 1)
        std::unordered_set<uint16_t > hConnections; //size * (size - 1)
        uint8_t size;
    public:
        explicit Map(uint8_t size);
        /*  GameMap::Map::Map(uint8_t size)
         * This initialises the map size and will always square the value given
         * making the map always the shape of a square
         * */
        ~Map();

        void addRoom(int x, int y, Room *room);
        /*  Map::addRoom(int x, int y, Room *room)
         * This adds the room pointer with default options to the map at the
         * x and y coordinates, this is an easier alternative to entering the
         * vector's position whilst staying in the relative map position
         * */

        void addRoom(int pos, Room *room);
        /*  Map::addRoom(int pos, Room *room)
         * This adds the room pointer with default options on to the map vector
         * using its position, this skips using the math expression to find the
         * vector position
         * */

        void addRoom(int x, int y, Room *room, uint8_t options);
        /*  Map::addRoom(int x, int y, Room *room, uint8_t options)
         * This adds a room pointer at the x and y position on the map with a
         * specified bit field option for connections between using GameMap::RoomOptions
         * */

        void addRoom(int pos, Room *room, uint8_t options);
        /*  Map::addRoom(int pos, Room *room, uint8_t options)
         * This adds a room pointer at the vector's position with specified
         * bit field options using GameMap::RoomOptions
         * */

        int position(int x, int y);
        /*  Map::position(int x, int y)
         * This will return the vector position from x and y coordinates
         * */

        void run();
        /*  Map::run()
         * This will run through all the connections between the rooms and add
         * the relative exits to the room pointers
         * */

        void print();
        /*  Map::print()
         * This will print a map of the vector with room's ID showing where they are
         * in the map and hash tags showing null locations in the map
         * */

    };
    class RoomOptions {
    public:
        static uint8_t AllDirections;
        static uint8_t North;
        static uint8_t East;
        static uint8_t West;
        static uint8_t NotNorth;
        static uint8_t NotEast;
        static uint8_t NotSouth;
        static uint8_t NotWest;
        static uint8_t South;
    };
}

#endif //TEXTADV_GAMEMAP_H
