#include "BoxColliderComponent.h"

BoxColliderComponent::BoxColliderComponent()
{
}

void BoxColliderComponent::Init()
{
	_position = &entity->GetComponent<PositionComponent>();
	_sprite = &entity->GetComponent<SpriteComponent>();
}

float BoxColliderComponent::Left() noexcept
{
	return _position->GetX();
}

float BoxColliderComponent::Right() noexcept
{
	return _position->GetX() + _sprite->srcRect.w;
}

float BoxColliderComponent::Top() noexcept
{
	return _position->GetY();
}

float BoxColliderComponent::Bottom() noexcept
{
	return _position->GetY() + _sprite->srcRect.h;
}

BoxColliderComponent::~BoxColliderComponent()
{
	delete _localPosition;
}
