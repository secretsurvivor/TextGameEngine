#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameMap.h"
#include "FileHandle.h"

#define CommandCase(name) case (int)((name[0] - 32) + ((name[1] - 32) * 90)) : commandOk = true;
#define CommandCaseEx(name, Abbr) case (int)(Abbr[0] - 32) : case (int)((name[0] - 32) + ((name[1] - 32) * 90)) : commandOk = true;
#define SecondVerb std::string secondVerb = endOfVerb == 255 ? "" : &commandBuffer[endOfVerb + 1];


using std::string;
using std::unique_ptr;

std::string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto* r1 = new Room(1, &r1name, &r1desc); // Forest Clearing
    auto* r2 = new Room(2, &r2name, &r2desc); // Old Watch Tower
    auto* r3 = new Room(3, &r3name, &r3desc); // Abandoned Camp
    auto* r4 = new Room(4, &r4name, &r4desc); // Path ending
    auto* r5 = new Room(5, &r5name, &r5desc); // Unfinished Room
    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);

    auto* stick = new GameObject(1, &obj1Name, &obj1Desc, &obj1Key); // Stick
    auto* key = new GameObject(2, &obj2Name, &obj2Desc, &obj2Key); // Key
    auto* note = new GameObject(3, &obj3Name, &obj3Desc, &obj3Key); // Note
    auto* backpack = new GameObject(4, &obj4Name, &obj4Desc, &obj4Key); // Backpack
    GameObject::addGameObject(stick);
    GameObject::addGameObject(note);
    GameObject::addGameObject(key);
    GameObject::addGameObject(backpack);

    r1->addItem(1);
    r3->addItem(3);
    r3->addItem(4);
    r4->addItem(2);

    /*
     *  2:  # # 5
     *  1:  2 3 4
     *  0:  1 # #
     *      0 1 2
     * */
    GameMap::Map map(3);
    map.addRoom(0, 0, r1, GameMap::RoomOptions::North);
    map.addRoom(0, 1, r2, GameMap::RoomOptions::South | GameMap::RoomOptions::East);
    map.addRoom(1, 1, r3);
    map.addRoom(2, 1, r4);
    map.addRoom(2, 2, r5, GameMap::RoomOptions::AllDirections | GameMap::RoomOptions::NotEast);
    map.run();
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(1);
}

#define CHAR_OFFSET 32
#define CHAR_COUNT 90

/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    while (!gameOver) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        uint8_t endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        int sum = (commandBuffer[0] - CHAR_OFFSET) + (commandBuffer[1] != CHAR_OFFSET && commandBuffer[1] != 0 ? (commandBuffer[1] - CHAR_OFFSET) * CHAR_COUNT : 0); // This converts the text into int
        switch(sum) {
            CommandCaseEx("north", "n")
                currentState->goTo(currentState->getCurrentRoom()->getNorth());
                break;
            CommandCaseEx("east", "e")
                currentState->goTo(currentState->getCurrentRoom()->getEast());
                break;
            CommandCaseEx("south", "s")
                currentState->goTo(currentState->getCurrentRoom()->getSouth());
                break;
            CommandCaseEx("west", "w")
                currentState->goTo(currentState->getCurrentRoom()->getWest());
                break;
            CommandCaseEx("inventory", "i")
                currentState->printInventory();
                break;
            CommandCase("describe")
                currentState->getCurrentRoom()->describe();
                break;
            CommandCase("examine")
            {   SecondVerb
                if (currentState->getInventory()->objectPresent(&secondVerb)) {
                    GameObject::gameobjects[currentState->getInventory()->get(&secondVerb)]->inspect();
                } else if (currentState->getCurrentRoom()->getObjects()->objectPresent(&secondVerb)) {
                    GameObject::gameobjects[currentState->getCurrentRoom()->getObjects()->get(&secondVerb)]->inspect();
                } else {
                    wrapOut(&secondVerb);
                    wrapOut(&itemNotFound);
                    wrapEndPara();
                }
            }
                break;
            CommandCaseEx("get", "g")
            {   SecondVerb
                uint16_t obj = currentState->getCurrentRoom()->getObjects()->get(&secondVerb);
                if (obj > 0){
                    currentState->addToInventory(obj);
                    currentState->getCurrentRoom()->removeItem(obj);
                } else {
                    wrapOut(&secondVerb);
                    wrapOut(&itemNotFound);
                    wrapEndPara();
                }
            } break;
            CommandCaseEx("drop", "d")
            {   SecondVerb
                uint16_t obj = currentState->getInventory()->get(&secondVerb);
                if (obj > 0){
                    currentState->getCurrentRoom()->addItem(obj);
                    currentState->removeFromInventory(obj);
                } else {
                    wrapOut(&secondVerb);
                    wrapOut(&itemNotFound);
                    wrapEndPara();
                }
            } break;
            CommandCase("save")
            {
                bool b = true;
                for (std::pair<uint16_t, Room*> element : Room::rooms){
                    if (element.second->getHash() != element.second->getObjects()->hashCode()){
                        int feed = FileHandle::Save(element.second);
                        if (feed == 1) {
                            b = false;
                            wrapOut(&fileNotFoundError);
                        } else if (feed == 2) {
                            b = false;
                            wrapOut(&writingError);
                        }
                    } else if (FileHandle::RoomSaved(element.second->getID())){
                        int feed = FileHandle::RemoveRoom(element.second->getID());
                    }
                }
                int feed = FileHandle::Save(currentState);
                if (feed == 1){
                    b = false;
                    wrapOut(&fileNotFoundError);
                } else if (feed == 2){
                    b = false;
                    wrapOut(&writingError);
                }
                if (b){
                    wrapOut(&saved);
                }
                wrapEndPara();
            } break;
            CommandCase("load")
            {
                FileHandle::LoadAllRooms();
                int feed = FileHandle::LoadState(currentState);
                if (feed == 0){
                    wrapOut(&loaded);
                    currentState->announceLoc();
                } else if (feed == 1){
                    wrapOut(&fileNotFoundError);
                } else if (feed == 3){
                    wrapOut(&readingError);
                }
                wrapEndPara();
            } break;
            CommandCaseEx("quit", "q")
                gameOver = true;
                break;
            }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
}


int main() {
    initWordWrap();
    initRooms();
    Room::hashRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}