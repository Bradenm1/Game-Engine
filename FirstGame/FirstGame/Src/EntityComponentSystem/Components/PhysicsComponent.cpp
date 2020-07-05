#include "PhysicsComponent.h"
#include "BoxColliderComponent.h"

PhysicsComponent::PhysicsComponent()
{
}

void PhysicsComponent::Init()
{
	_position = &entity->GetComponent<PositionComponent>();
	Velocity = new Vector2f();
}

void PhysicsComponent::Update()
{
	_position->SetX(_position->GetX() + Velocity->x);
	_position->SetY(_position->GetY() + Velocity->y);
	Velocity->x = 0;
	Velocity->y = 0;
}

PhysicsComponent::~PhysicsComponent()
{
	delete Velocity;
}
