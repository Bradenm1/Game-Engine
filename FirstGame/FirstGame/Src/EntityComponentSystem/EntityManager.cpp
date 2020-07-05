#include "EntityManager.h"
#include "../Game.hpp"
#include "../Math/Hashing.h"

void EntityManager::Update()
{
    std::vector<Entity*>& GSprites = GetEntitiesByGroup("Sprite");
    std::vector<Entity*>& GWalls = GetEntitiesByGroup("Wall");

    for (auto& w : GWalls)
    {
        for (auto& spr : GSprites)
        {
            Entity::AABB(spr, w);
        }
    }

    for (auto& e : _entities)
    {
        e->Update();
    }
}

void EntityManager::Render()
{
    for (auto& e : _entities)
    {
        e->Render();
    }
}

void EntityManager::Refresh()
{
    std::map<unsigned, std::vector<Entity*>>::iterator it;
    for (it = _groupedEntities.begin(); it != _groupedEntities.end(); it++)
    {
        std::vector<Entity*> entites = it->second;
        unsigned hash = it->first;
        entites.erase(std::remove_if(std::begin(entites), std::end(entites),
            [hash](Entity* mEntity)
            {
                return mEntity == NULL || !mEntity->IsAlive() ||
                    !mEntity->HasGroup(hash);
            }),
            std::end(entites));
    }

    _entities.erase(
        std::remove_if(std::begin(_entities), std::end(_entities),
            [](const std::unique_ptr<Entity>& mEntity)
            {
                mEntity->CollisionDirection.reset();
                return mEntity == NULL || !mEntity->IsAlive();
            }),
        std::end(_entities));
}

void EntityManager::AddToGroup(Entity* entity, const char* group)
{
    _groupedEntities[Hashing::Hash(group)].emplace_back(entity);
}

void EntityManager::RemoveFromGroup(Entity* entity, const char* group)
{

}

std::vector<Entity*>& EntityManager::GetEntitiesByGroup(const char* group)
{
    return _groupedEntities[Hashing::Hash(group)];
}

Entity& EntityManager::AddEntity()
{
    Entity* e = new Entity(*this);
    std::unique_ptr<Entity> uPtr{ e };
    _entities.emplace_back(std::move(uPtr));
    return *e;
}

Entity* EntityManager::Lua_AddEntity()
{
    Entity* e = new Entity(*this);
    std::unique_ptr<Entity> uPtr{ e };
    _entities.emplace_back(std::move(uPtr));
    return e;
}
