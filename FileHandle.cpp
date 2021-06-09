//
// Created by 18074751 on 29/10/2019.
//

#include <windows.h>
#include "FileHandle.h"

struct ROOM_FILE {
    uint16_t ID;
};
struct OBJECT_FILE {
    uint16_t ID;
};
struct STATE_FILE {
    uint16_t currentRoom;
};
struct BINARYTABLE {
    uint8_t type; /* Type of file structure */
    uint16_t objS; /* Object list length */
};
const std::size_t STATE = sizeof(STATE_FILE), OBJECT = sizeof(OBJECT_FILE), TABLE = sizeof(BINARYTABLE);

OBJECT_FILE* Serialise(GameObject* toSerialise){
    auto* structure = (OBJECT_FILE*)malloc(sizeof(OBJECT_FILE));

    structure->ID = toSerialise->getID();

    return structure;
}
STATE_FILE* Serialise(State* toSerialise){
    auto* structure = (STATE_FILE*)malloc(sizeof(STATE_FILE));

    structure->currentRoom = toSerialise->getCurrentRoomID();

    return structure;
}

/*  FileFeedback
 *
 * 0 : Confirmed,
 * 1 : FileNotFound,
 * 2 : WritingError,
 * 3 : ReadingError,
 * -1 : UnknownError
 * */

int FileHandle::Save(State* toSave){
    CreateDirectory("save", nullptr);
    std::ofstream file("save\\state.dat", std::ios::out | std::ios::binary);
    if (!file){ /* File not found */
        return 1;
    }

    STATE_FILE* state = Serialise(toSave);
    int size = toSave->getInventory()->size();
    std::vector<OBJECT_FILE*> objectVector;
    if (size > 0) {
        objectVector.reserve(size);
        for (auto i = toSave->getInventory()->begin(); i != toSave->getInventory()->end(); i++){
            objectVector.push_back((Serialise(GameObject::gameobjects[*i])));
        }
    }
    BINARYTABLE table{};
    table.type = 1;
    table.objS = size;

    file.write((char *) &table, TABLE);
    file.write((char *) state, STATE);
    for (OBJECT_FILE* obj : objectVector){
        file.write((char *) obj, OBJECT);
    }
    file.close();

    delete state;
    for (OBJECT_FILE* obj : objectVector){
        delete obj;
    }

    if (!file.good()){ /* Error during writing process */
        return 2;
    } else {
        return 0;
    }
}

int FileHandle::Save(Room* toSave){
    CreateDirectory("save", nullptr);
    std::ofstream file("save\\" + std::to_string(toSave->getID()) + ".dat", std::ios::out | std::ios::binary);
    if (!file){ /* File not found */
        return 1;
    }

    int size = toSave->getObjects()->size();
    std::vector<OBJECT_FILE*> objectVector;
    if (size > 0) {
        objectVector.reserve(size);
        for (auto i = toSave->getObjects()->begin(); i != toSave->getObjects()->end(); ++i){
            objectVector.push_back((Serialise(GameObject::gameobjects[*i])));
        }
    }
    BINARYTABLE table{};
    table.type = 0;
    table.objS = size;

    file.write((char *) &table, TABLE);
    for (OBJECT_FILE* obj : objectVector){
        file.write((char *) obj, OBJECT);
    }
    file.close();

    for (OBJECT_FILE* obj : objectVector){
        delete obj;
    }

    if (!file.good()){ /* Error during writing process */
        return 2;
    } else {
        return 0;
    }
}

int FileHandle::LoadState(State *toLoad) {
    std::ifstream file ("save\\state.dat", std::ios::in | std::ios::binary);
    if (!file){ /* File not found */
        return 1;
    }

    BINARYTABLE table{};
    STATE_FILE state{};
    std::vector<OBJECT_FILE> objectVector;
    file.read((char *) &table, TABLE);
    if (table.type != 1) {return -1;}
    objectVector.resize(table.objS);
    file.read((char *) &state, STATE);
    for (int i = 0; i < table.objS; i++){
        OBJECT_FILE obj{};
        file.read((char *) &obj, OBJECT);
        objectVector.push_back(obj);
    }
    file.close();

    toLoad->setCurrentRoom(state.currentRoom);
    toLoad->clearInventory();
    for (OBJECT_FILE obj : objectVector){
        toLoad->setInventory(obj.ID);
    }

    return 0;
}

void FileHandle::LoadAllRooms() {
    std::vector<uint16_t> roomVector = GetRoomSavedList();
    for (uint16_t r : roomVector){
        int feed = LoadRoom(r);
    }
}

int FileHandle::LoadRoom(uint16_t roomID) {
    return GetRoom(roomID, Room::rooms[roomID]);
}

int FileHandle::GetRoom(uint16_t roomID, Room *toLoad) {
    std::ifstream file ("save\\" + std::to_string(roomID) + ".dat", std::ios::in | std::ios::binary);
    if (!file){ /* File not found */
        return 1;
    }

    BINARYTABLE table{};
    std::vector<OBJECT_FILE> objectVector;
    file.read((char *)&table, TABLE);
    objectVector.resize(table.objS);
    for (int i = 0; i < table.objS; i++){
        OBJECT_FILE obj{};
        file.read((char *) &obj, OBJECT);
        objectVector.push_back(obj);
    }
    file.close();

    toLoad->getObjects()->clear();
    for (OBJECT_FILE obj : objectVector){
        toLoad->addItem(obj.ID);
    }

    return 0;
}

bool FileHandle::StateSaved() {
    std::ifstream file("save\\state.dat");
    return file.good();
}

bool FileHandle::RoomSaved(uint16_t roomID) {
    std::ifstream file("save\\" + std::to_string(roomID) + ".dat");
    return file.good();
}

int FileHandle::RemoveRoom(uint16_t roomID) {
    return std::remove(std::string("save\\" + std::to_string(roomID) + ".dat").c_str());
}

int FileHandle::RemoveState() {
    return std::remove("save\\state.dat");
}

std::vector<uint16_t> FileHandle::GetRoomSavedList() {
    std::vector<uint16_t> roomVector;
    WIN32_FIND_DATA fd;
    HANDLE find = ::FindFirstFile("save\\*.dat", &fd);
    if (find != INVALID_HANDLE_VALUE){
        do {
            if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0){
                std::string name = std::string(fd.cFileName);
                if (name != "state.dat"){
                    roomVector.push_back(std::stoi(name));
                }
            }
        } while (::FindNextFile(find, &fd));
        ::FindClose(find);
    }
    return roomVector;
}
