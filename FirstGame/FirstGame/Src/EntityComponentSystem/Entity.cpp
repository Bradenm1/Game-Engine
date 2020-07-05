#include "Entity.h"
#include "EntityManager.h"
#include "Components/PhysicsComponent.h"
#include "Components/BoxColliderComponent.h"
#include "../Math/Hashing.h"

Entity::Entity(EntityManager& manager)
{
    _manager = &manager;
}

Entity::~Entity()
{
    delete &_components;
    delete &_componentBitset;
}

void Entity::AABB(Entity* mA, Entity* mB)
{
    if (!mA->HasComponent<BoxColliderComponent>() || !mB->HasComponent<BoxColliderComponent>() || !mA->HasComponent<PhysicsComponent>()) return;
    BoxColliderComponent* mASpr = &mA->GetComponent<BoxColliderComponent>();
    BoxColliderComponent* mBSpr = &mB->GetComponent<BoxColliderComponent>();

    if (!BoxColliderComponent::IsIntersecting(*mASpr, *mBSpr)) return;
    PhysicsComponent* mAPhy = &mA->GetComponent<PhysicsComponent>();

    float overlapLeft = mASpr->Right() - mBSpr->Left();
    float overlapRight = mBSpr->Right() - mASpr->Left();
    float overlapTop = mASpr->Bottom() - mBSpr->Top();
    float overlapBottom = mBSpr->Bottom() - mASpr->Top();

    bool fromLeft = abs(overlapLeft) < abs(overlapRight);
    bool fromTop = abs(overlapTop) < abs(overlapBottom);

    float minOverlapX = fromLeft ? overlapLeft : overlapRight;
    float minOverlapY = fromTop ? overlapTop : overlapBottom;
    if (minOverlapX == 0 && minOverlapY == 0) return;

    if (abs(minOverlapX) < abs(minOverlapY)) {
        if (fromLeft) {
            mAPhy->Velocity->x -= minOverlapX;
            mA->CollisionDirection.set(0);
        }
        else {
            mAPhy->Velocity->x += minOverlapX;
            mA->CollisionDirection.set(1);
        }
    }
    else {
        if (fromTop) {
            mAPhy->Velocity->y -= minOverlapY;
            mA->CollisionDirection.set(2);
        }
        else {
            mAPhy->Velocity->y += minOverlapY;
            mA->CollisionDirection.set(3);
        }
    }
}

void Entity::Update()
{
    for (auto& c : _components)
    {
        c->Update();
    }
}

void Entity::Render()
{
    for (auto& c : _components)
    {
        c->Render();
    }
}

bool Entity::HasGroup(const char* mGroup) const noexcept
{
    return _containedGroup.at(Hashing::Hash(mGroup));
}

bool Entity::HasGroup(unsigned mGroup) const noexcept
{
    return _containedGroup.at(mGroup);
}

void Entity::AddGroup(const char* mGroup) noexcept
{
    _containedGroup[Hashing::Hash(mGroup)] = true;
    _manager->AddToGroup(this, mGroup);
}

void Entity::DelGroup(const char* mGroup) noexcept
{
    _manager->RemoveFromGroup(this, mGroup);
    _containedGroup[Hashing::Hash(mGroup)] = false;
}

bool Entity::Lua_AddComponent(int component)
{
    switch (component)
    //switch (Hashing::Hash(className))
    {
    case 0:
        AddComponent<PositionComponent>();
        break;
    case 1:
        AddComponent<PhysicsComponent>();
        break;
    case 2:
        AddComponent<SpriteComponent>();
        break;
    case 3:
        AddComponent<ControlMovementComponent>();
        break;
    case 4:
        AddComponent<BoxColliderComponent>();
        break;
    default:
        return false;
        break;
    }
    return true;
}

PositionComponent* Entity::Lua_GetComponentPositionComponent()
{
    return &GetComponent<PositionComponent>();
}

SpriteComponent* Entity::Lua_GetComponentSpriteComponent()
{
    return &GetComponent<SpriteComponent>();
}

BoxColliderComponent* Entity::Lua_GetComponentBoxColliderComponent()
{
	return &GetComponent<BoxColliderComponent>();
}

ControlMovementComponent* Entity::Lua_GetComponentControlMovementComponent()
{
    return &GetComponent<ControlMovementComponent>();
}

PhysicsComponent* Entity::Lua_GetComponentPhysicsComponent()
{
    return &GetComponent<PhysicsComponent>();
}
