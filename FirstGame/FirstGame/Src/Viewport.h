#pragma once

#include "EntityComponentSystem/Entity.h"
#include "Game.hpp"

class ViewPort {
	PositionComponent* TargetEntityPosition;
	int _viewportHalfWidth;
	int _viewportHalfHeight;
public:
	Entity* TargetEntity;
	SDL_Rect Viewport;

	void Init(Entity* target);
	void Update();
};