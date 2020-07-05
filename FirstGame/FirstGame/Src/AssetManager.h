#pragma once
#include <map>
#include "SpriteSheet.h"

using namespace std;

class SpriteSheet;
struct AssetManager {
public:
	static map<unsigned, SpriteSheet*> AllSpriteSheets;

	static void AddSpriteSheet(const char* index, const char* assetLoction);
	static void AddSpriteSheet(const char* index, SpriteSheet* spriteSheet);
	static void AddSpriteSheet(unsigned hash, SpriteSheet* spriteSheet);
	static SpriteSheet* GetSpriteSheet(const char* index);
	static SpriteSheet* GetSpriteSheet(unsigned hash);

    //LUA
    static void Lua_AddSpriteSheet(const char* index, const char* assetLoction);
    static SpriteSheet* Lua_GetSpriteSheet(const char* index);

    static void RegisterLua(lua_State* L)
    {
        using namespace luabridge;
        getGlobalNamespace(L) //global namespace to lua
            .beginNamespace("Engine") //our defined namespace (w.e we want to call it)
                .beginClass<AssetManager>("AssetManager") //define class object
                    .addStaticFunction("addSpriteSheet", &AssetManager::Lua_AddSpriteSheet) //reg. setName function
                    .addStaticFunction("getSpriteSheet", &AssetManager::Lua_GetSpriteSheet) //reg. setName function
                .endClass() //end class
            .endNamespace(); //end namespace
    }
};