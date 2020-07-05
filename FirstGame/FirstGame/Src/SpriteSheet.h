#pragma once

#include "Game.hpp"
#include <lua.hpp>

class SpriteSheet {
private:
	SDL_Texture* _spriteSheet;
public:
    SpriteSheet();
	SpriteSheet(const char* spriteSheetLocation);
	void Render(SDL_Rect srcRect, SDL_FRect destRect);
    ~SpriteSheet();

    //LUA 

    static void RegisterLua(lua_State* L)
    {
        using namespace luabridge;
        getGlobalNamespace(L) //global namespace to lua
            .beginNamespace("Engine") //our defined namespace (w.e we want to call it)
                .beginClass<SpriteSheet>("SpriteSheet") //define class object
                    .addConstructor<void (*) (void)>()
                    .addConstructor<void (*) (const char*)>()
                .endClass() //end class
            .endNamespace(); //end namespace
    }
};