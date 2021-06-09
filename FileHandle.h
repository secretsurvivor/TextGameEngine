//
// Created by 18074751 on 29/10/2019.
//

#ifndef TEXTADV_FILEHANDLE_H
#define TEXTADV_FILEHANDLE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Room.h"
#include "State.h"


class FileHandle {
private:
public:
    static int Save(State* toSave);
    /*  FileHandle::Save(State* toSave)
     * Given a state class it will save its variables into the file state.dat
     *
     * The return value is to signal any errors that may have passed when saving
     * */
    static int Save(Room* toSave);
    /*  FileHandle::Save(Room* toSave)
     * Given a Room class it will save all its variables into a file with the same
     * ID as the Room class
     *
     * The return value is to signal any errors that may have passed when saving
     * */
    static int LoadState(State* toLoad);
    /*  FileHandle::LoadState()
     * This will load any variables found in the state.dat file directly into
     * the State class pointer passed into the parameter
     *
     * The return value is to signal any errors that may have passed when loading
     * */
    static void LoadAllRooms();
    /*  FileHandle::LoadAllRooms()
     * This will load all rooms found directly into the unordered_map
     *
     * The return value is to signal any errors that may have passed when loading
     * */
    static int LoadRoom(uint16_t roomID);
    /*  FileHandle::LoadRoom(long roomID)
     * This will load a certain room that matches the Room ID into the
     * unordered_map
     *
     * The return value is to signal any errors that may have passed when loading
     * */
    static int GetRoom(uint16_t roomID, Room* toLoad);
    /*  FileHandle::GetRoom(long roomID, Room* toLoad)
     * This will load the room of the given ID into the given pointer
     *
     * The return value is to signal any errors that may have passed when loading
     * */
    static std::vector<uint16_t> GetRoomSavedList();
    /*  FileHandle::GetRoomSavedList()
     * This returns the list of rooms that are saved in IDs
     * */
    static bool StateSaved();
    /*  FileHandle::StateSaved()
     * This will return true if a State class has been saved
     * */
    static bool RoomSaved(uint16_t roomID);
    /*  FileHandle::RoomSaved(long roomID)
     * This will return true if the Room with the same ID has been saved
     * */
    static int RemoveRoom(uint16_t roomID);
    /*  FileHandle::RemoveRoom(uint16_t roomID)
     * This removes any save file for a room using its room ID
     *
     * The return value is any errors that may of occurred during deletion
     * */
    static int RemoveState();
    /*  FileHandle::RemoveState()
     * This removes the save file of the player's state
     *
     * The return value is any errors that may of occurred during deletion
     * */
};


#endif //TEXTADV_FILEHANDLE_H
