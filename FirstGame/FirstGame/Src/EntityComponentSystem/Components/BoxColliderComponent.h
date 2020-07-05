#pragma once

#ifndef BOXCOLLIDERCOMPONENT_H // #include guards
#define BOXCOLLIDERCOMPONENT_H

class SpriteComponent;
#include "SpriteComponent.h"

class BoxColliderComponent : public Component {
private:
	Vector2f* _localPosition;
	PositionComponent* _position;
	SpriteComponent* _sprite;

public:
	BoxColliderComponent();
	void Init() override;

	float Left() noexcept;
	float Right() noexcept;
	float Top() noexcept;
	float Bottom() noexcept;

	static bool IsIntersecting(BoxColliderComponent& bA, BoxColliderComponent& bB) noexcept
	{
		return bA.Right() >= bB.Left() && bA.Left() <= bB.Right() &&
			bA.Bottom() >= bB.Top() && bA.Top() <= bB.Bottom();
	}

	~BoxColliderComponent();

	//LUA

	static void RegisterLua(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L) //global namespace to lua
			.beginNamespace("Engine") //our defined namespace (w.e we want to call it)
			.deriveClass<BoxColliderComponent, Component>("BoxColliderComponent") //define class object
			.addStaticFunction("isIntersecting", &BoxColliderComponent::IsIntersecting) //reg. setName function
			.endClass() //end class
			.endNamespace(); //end namespace
	}
};

#endif