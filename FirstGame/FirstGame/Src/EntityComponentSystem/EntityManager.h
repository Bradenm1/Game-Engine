#pragma once

#ifndef ENTITYMANAGER_H // #include guards
#define ENTITYMANAGER_H

#include "Entity.h"

struct CollisionGroups {
    const char* group1;
    const char* group2;
};

class EntityManager
{
private:
    std::vector<std::unique_ptr<Entity>> _entities;
    std::map<unsigned, std::vector<Entity*>> _groupedEntities;
    std::vector<std::unique_ptr<CollisionGroups>> _collsionGroups;

public:
    void Update();
    void Render();
    void Refresh();

    void AddToGroup(Entity* entity, const char* group);
    void RemoveFromGroup(Entity* entity, const char* group);
    std::vector<Entity*>& GetEntitiesByGroup(const char* group);
    Entity& AddEntity();

	Entity* Lua_AddEntity();

    //LUA

    static void RegisterLua(lua_State* L)
    {
        using namespace luabridge;
        getGlobalNamespace(L) //global namespace to lua
            .beginNamespace("Engine") //our defined namespace (w.e we want to call it)
                .beginClass<EntityManager>("EntityManager") //define class object
                    .addFunction("createEntity", &EntityManager::Lua_AddEntity) //reg. setName function
                    .addFunction("addToGroup", &EntityManager::AddToGroup) //reg. setName function
                    .addFunction("removeFromGroup", &EntityManager::RemoveFromGroup) //reg. setName function
                .endClass() //end class
            .endNamespace(); //end namespace
    }
};

#endif