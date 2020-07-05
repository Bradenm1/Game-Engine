#pragma once

#pragma once
#ifndef ENTITY_H // #include guards
#define ENTITY_H

#include <vector>
#include <array>
#include <map>
#include <assert.h>
#include "../Lua/LuaManager.h"

class EntityManager;
class Entity;
class PositionComponent;
class SpriteComponent;
class BoxColliderComponent;
class ControlMovementComponent;
class PhysicsComponent;
class ControlMovementComponent;
class PhysicsComponent;
#include "Component.h"

class Entity
{
private:
    EntityManager* _manager;

    std::vector<std::unique_ptr<Component>> _components;
    std::map<unsigned int, bool> _containedGroup;
    ComponentArray _componentArray;
    ComponentBitset _componentBitset;

    bool _alive = true;

public:
    std::bitset<4> CollisionDirection;

    float MovementSpeed = 5;

    Entity(EntityManager& manager);
    ~Entity();
    static void AABB(Entity* mA, Entity* mB);

    void Update();
    void Render();
    bool IsAlive() const { return _alive; }
    void Destroy() { _alive = false; }

#pragma region Group_Functions
    bool HasGroup(const char* mGroup) const noexcept;
    bool HasGroup(unsigned mGroup) const noexcept;
    void AddGroup(const char* mGroup) noexcept;
    void DelGroup(const char* mGroup) noexcept;
#pragma endregion

#pragma region Component_Functions
    template <typename T>
    T& GetComponent() const {
        assert(HasComponent<T>());
        auto ptr(_componentArray[getComponentTypeID<T>()]);
        return *reinterpret_cast<T*>(ptr);
    };

    template <typename T>
    bool HasComponent() const {
        return _componentBitset[getComponentTypeID<T>()];
    };

    template <typename T, typename... TArgs>
    T& AddComponent(TArgs&&... mArgs) {
        assert(!HasComponent<T>());

        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{ c };
        _components.emplace_back(std::move(uPtr));

        _componentArray[getComponentTypeID<T>()] = c;
        _componentBitset[getComponentTypeID<T>()] = true;

        c->Init();
        return *c;
    };
#pragma endregion

    //LUA
    bool Lua_AddComponent(int component);
    SpriteComponent* Lua_GetComponentSpriteComponent();
    BoxColliderComponent* Lua_GetComponentBoxColliderComponent();
    ControlMovementComponent* Lua_GetComponentControlMovementComponent();
    PhysicsComponent* Lua_GetComponentPhysicsComponent();
    PositionComponent* Lua_GetComponentPositionComponent();

    static void RegisterLua(lua_State* L)
    {
        using namespace luabridge;
        getGlobalNamespace(L) //global namespace to lua
            .beginNamespace("Engine") //our defined namespace (w.e we want to call it)
            .beginClass<Entity>("Entity") //define class object
            .addFunction("addGroup", &Entity::AddGroup) //reg. setName function
            .addFunction("addComponent", &Entity::Lua_AddComponent) //reg. setName function
            .addFunction("getPositionComponent", &Entity::Lua_GetComponentPositionComponent) //reg. setName function
            .addFunction("getSpriteComponent", &Entity::Lua_GetComponentSpriteComponent) //reg. setName function
            .addFunction("getBoxColliderComponent", &Entity::Lua_GetComponentBoxColliderComponent) //reg. setName function
            .addFunction("getControlMovementComponent", &Entity::Lua_GetComponentControlMovementComponent) //reg. setName function
            .addFunction("getPhysicsComponent", &Entity::Lua_GetComponentPhysicsComponent) //reg. setName function
            .endClass() //end class
            .endNamespace(); //end namespace
    };
};

#endif
