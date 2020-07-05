#pragma once

#ifndef SPRITECONPONMENT_H
#define SPRITECONPONMENT_H

#define SPRITESIZE 16

#include "../../TextureManager.h"
#include "PositionComponent.h"

class SpriteSheet;
class SpriteComponent : public Component {
private:
	PositionComponent* _position = nullptr;
	SpriteSheet* _spriteSheet = nullptr;
public:
	SDL_FRect destRect;
	SDL_Rect srcRect;

	SpriteComponent();
	SpriteComponent(SpriteSheet* spriteSheet);
	SpriteComponent(SpriteSheet* spriteSheet, int x, int y);
	void SetSpriteSheet(SpriteSheet* spriteSheet);
	void SetSpriteSheet(SpriteSheet* spriteSheet, int x, int y);
	void SetSpiteSourceRender(int x, int y);
	void SetSpiteSourceRenderSize(int w, int h);
	void Init() override;
	void Update() override;
	void Render() override;
	~SpriteComponent();

	//LUA
	void Lua_SetSpriteSheet(SpriteSheet* spriteSheet, int x, int y);

	static void RegisterLua(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L) //global namespace to lua
			.beginNamespace("Engine") //our defined namespace (w.e we want to call it)
			.deriveClass <SpriteComponent, Component>("SpriteComponent")
			.addConstructor<void (*) (void)>()
			.addFunction("setSpriteSheet", &SpriteComponent::Lua_SetSpriteSheet)
			.endClass()
			.endNamespace(); //end namespace
	}
};

#endif
