#pragma once

#ifndef POSITIONCOMPONENT_H // #include guards
#define POSITIONCOMPONENT_H

#include "../Entity.h"
#include "../../Math/Vector2.h"

class PositionComponent : public Component {
private:
	Vector2f* _position = new Vector2f();

public:
	PositionComponent();
	PositionComponent(float x, float y);
	void Init() override;
	~PositionComponent();

	inline float GetX() { return _position->x; };
	inline float GetY() { return _position->y; };
	inline void SetX(float x) 
	{ 
		if (x < 0) x = 0;
		_position->x = x;
	};
	inline void SetY(float y) 
	{ 
		if (y < 0) y = 0;
		_position->y = y; 
	};

	//LUA

	static void RegisterLua(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L) //global namespace to lua
			.beginNamespace("Engine") //our defined namespace (w.e we want to call it)
			.deriveClass <PositionComponent, Component>("PositionComponent")
			.addFunction("getX", &PositionComponent::GetX)
			.addFunction("getY", &PositionComponent::GetY)
			.addFunction("setX", &PositionComponent::SetX)
			.addFunction("setY", &PositionComponent::SetY)
			.endClass()
			.endNamespace(); //end namespace
	}
};

#endif