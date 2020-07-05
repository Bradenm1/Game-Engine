#pragma once

#ifndef CONPONENT_H // #include guards
#define CONPONENT_H

#include <algorithm>
#include <bitset>

using ComponentID = std::size_t;
class Entity;

using ComponentID = std::size_t;
using Group = std::size_t;
constexpr std::size_t maxComponents{ 32 };

class Component
{
public:
    Entity* entity;

    virtual void Init() {}
    virtual void Update() {}
    virtual void Render() {}

    virtual ~Component() {}

    static void RegisterLua(lua_State* L)
    {
        using namespace luabridge;
        getGlobalNamespace(L) //global namespace to lua
            .beginNamespace("Engine") //our defined namespace (w.e we want to call it)
            .beginClass<Component>("Component") //define class object
            .endClass() //end class
            .endNamespace(); //end namespace
    }
};

using ComponentBitset = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

namespace InternalComponent
{
    inline ComponentID getUniqueComponentID() noexcept
    {
        static ComponentID lastID{ 0u };
        return lastID++;
    }
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");

    static ComponentID typeID{ InternalComponent::getUniqueComponentID() };
    return typeID;
}

#endif