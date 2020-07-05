#pragma once

#ifndef PHYSICSCOMPONENT_H // #include guards
#define PHYSICSCOMPONENT_H

#include "PositionComponent.h"

class PhysicsComponent : public Component {

private:
	PositionComponent* _position = nullptr;

public:
	Vector2f* Velocity;
	PhysicsComponent();

	void Init() override;
	void Update() override;

	~PhysicsComponent();

	//LUA

	static void RegisterLua(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L) //global namespace to lua
			.beginNamespace("Engine") //our defined namespace (w.e we want to call it)
			.deriveClass <PhysicsComponent, Component>("PhysicsComponent")
			.addProperty("velocity", &PhysicsComponent::Velocity)
			.endClass()
			.endNamespace(); //end namespace
	}
};

#endif