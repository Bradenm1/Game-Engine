#pragma once

#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "Lua/LuaManager.h"
#include "AssetManager.h"
#include "EntityComponentSystem/EntityManager.h"
class TileMap;
#include "TileMap.h"
class ViewPort;
#include "Viewport.h"

using namespace std;

enum GameGroup : std::size_t
{
	GSprite,
	GFloor,
	GWall,
};

class Game {

public:
	static Entity* Player;
	static EntityManager* EntityManager;
	static TileMap* TileMap;
	static SDL_Window* Window;
	static ViewPort* ViewPort;
	static SDL_Renderer* Renderer;
	static LuaManager* LuaManager;

	void Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	bool RunLuaInit();

	void LoadLuaFiles();
	void RegisterLuaFunctions();

	void CreatePlayer();
	void HandleEvents();
	void Update();
	void Render();
	void Destroy();

	bool IsRunning();

	//LUA

	static void RegisterLua(lua_State* L)
	{
		using namespace luabridge;
		getGlobalNamespace(L) //global namespace to lua
			.beginNamespace("Engine") //our defined namespace (w.e we want to call it)
				.beginClass<Game>("Game") //define class object
					.addStaticProperty("TileMap", &Game::TileMap)
					.addStaticProperty("ViewPort", &Game::ViewPort)
					.addStaticProperty("EntityManager", &Game::EntityManager)
					.addStaticProperty("Player", &Game::Player)
				.endClass() //end class
			.endNamespace(); //end namespace
	}

private:
	//int _cnt = 0;
	bool _isRunning;
	const float _renderScale = 2;

};

#endif