#pragma once

#define TileMapSizeX 64
#define TileMapSizeY 64

#include "EntityComponentSystem/Components.h"
#include "SpriteSheet.h"
#include "Layer.h"
#include <map>

class TileMap {

public:
	Entity* Map[TileMapSizeX][TileMapSizeY];
	std::map<unsigned, Layer*> Layers;

	void InitTileMap();
	void CreateTile(const char* layer, int x, int y, int sX, int sY);
	void CreateTile(unsigned layer, int x, int y, int sX, int sY);
	bool IsTileOutOfBounds(int x, int y);
	bool CheckTileExists(int x, int y);
	void AssignTile(Entity* tile, int x, int y);
	void AddLayer(unsigned hash, bool colide);
	void AddLayer(const char* name, bool colide);
	Layer* GetLayer(const char* name);
	Layer* GetLayer(unsigned hash);
	void SetTileSourceRender(int xT, int yT, int x, int y);
	void SetTileSourceRenderSize(int xT, int yT, int w, int h);

	//LUA
	void Lua_CreateTileChar(const char* layer, int x, int y, int sX, int sY);
	void Lua_CreateTileUnsigned(unsigned layer, int x, int y, int sX, int sY);
	void Lua_AddLayerChar(const char* name, bool colide);
	void Lua_AddLayerUnsigned(unsigned hash, bool colide);

	static void RegisterLua(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L) //global namespace to lua
			.beginNamespace("Engine") //our defined namespace (w.e we want to call it)
			.beginClass<TileMap>("TileMap") //define class object
			.addFunction("createTileChar", &TileMap::Lua_CreateTileChar) //reg. setName function
			.addFunction("createTileUnsigned", &TileMap::Lua_CreateTileUnsigned) //reg. setName function
			.addFunction("addLayerChar", &TileMap::Lua_AddLayerChar) //reg. setName function
			.addFunction("addLayerUnsigned", &TileMap::Lua_AddLayerUnsigned) //reg. setName function
			.endClass() //end class
			.endNamespace(); //end namespace
	}
};