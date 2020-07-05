#include "PositionComponent.h"

PositionComponent::PositionComponent()
{
	SetX(0);
	SetY(0);
}

PositionComponent::PositionComponent(float x, float y)
{
	this->SetX(x);
	this->SetY(y);
}

void PositionComponent::Init()
{
}

PositionComponent::~PositionComponent()
{
	//delete _position;
}
