#pragma once

#ifndef CONTROLMOVEMENTCOMPONENT_H // #include guards
#define CONTROLMOVEMENTCOMPONENT_H

#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "SDL.h"

class ControlMovementComponent : public Component {

private:
	PositionComponent* _position;
	PhysicsComponent* _physics;
	SDL_Event _event;
	float startingXPos = 0;
	float startingYPos = 0;
public:

	ControlMovementComponent();
	void Init() override;
	void Update() override;
	~ControlMovementComponent();

	//LUA

	static void RegisterLua(lua_State* L)
	{
	}
};

#endif