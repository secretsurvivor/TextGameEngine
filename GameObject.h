//
// Created by 18074751 on 17/10/2019.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H

#include <unordered_map>
#include <forward_list>
#include <cstdint>
#include "wordwrap.h"
#include "strings.h"

class GameObject {
private:
    const uint16_t ID;
    const std::string* name;
    const std::string* description;
    const std::string* keyword;
public:
    GameObject(const uint16_t ID, const std::string* _name, const std::string* _desc, const std::string* key);
    const uint16_t getID();
    const std::string* getName();
    const std::string* getDesc();
    const std::string* getKeyword();
    void inspect();
    void remove();
    static std::unordered_map<uint16_t, GameObject*> gameobjects;
    //static GameObject* addGameObject(const std::string* _name, const std::string* _desc, const std::string* key);
    static GameObject* addGameObject(GameObject* obj);
    std::size_t hashCode();
protected:
};

#endif //TEXTADV_GAMEOBJECT_H
