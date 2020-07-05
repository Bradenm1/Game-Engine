#include "Game.hpp"
#include "Math/Hashing.h"

Entity* Game::Player;
EntityManager* Game::EntityManager;
TileMap* Game::TileMap;
SDL_Window* Game::Window;
ViewPort* Game::ViewPort;
SDL_Renderer* Game::Renderer;
LuaManager* Game::LuaManager;

void Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	LuaManager::Init();
	RegisterLuaFunctions();
	LoadLuaFiles();

	int flags = 0;
	if (flags) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
	{
		cout << "SDL INIT RUNNING..." << endl;

		Window = SDL_CreateWindow("Title", xpos, ypos, width, height, flags);
		if (Window) {
			cout << "WINDOW INIT RUNNING..." << endl;
		}

		Renderer = SDL_CreateRenderer(Window, -1, 0);
		SDL_RenderSetScale(Renderer, _renderScale, _renderScale);

		if (Renderer) {
			cout << "RENDERER INIT RUNNING..." << endl;
		}

		_isRunning = true;
	}
	else {
		_isRunning = false;
	}

	RunLuaInit();
	//CreatePlayer();
	if (Player != NULL) ViewPort->Init(Player);
}

bool Game::RunLuaInit() 
{
	try 
	{
		luabridge::LuaRef ref = luabridge::LuaRef::getGlobal(LuaManager::LuaState, "Init")();
	}
	catch (const luabridge::LuaException & e) 
	{
		cout << "LUA INIT ERROR.. " << e.what() << endl;
		_isRunning = false;
		return false;
	}
	return true;
}

void Game::LoadLuaFiles() 
{
	LuaManager::LoadFile("LuaCore/Init.lua");
}

void Game::RegisterLuaFunctions() 
{
	RegisterLua(LuaManager::LuaState);
	AssetManager::RegisterLua(LuaManager::LuaState);
	EntityManager::RegisterLua(LuaManager::LuaState);
	SpriteSheet::RegisterLua(LuaManager::LuaState);
	TileMap::RegisterLua(LuaManager::LuaState);
	Component::RegisterLua(LuaManager::LuaState);
	PositionComponent::RegisterLua(LuaManager::LuaState);
	SpriteComponent::RegisterLua(LuaManager::LuaState);
	PhysicsComponent::RegisterLua(LuaManager::LuaState);
	ControlMovementComponent::RegisterLua(LuaManager::LuaState);
	BoxColliderComponent::RegisterLua(LuaManager::LuaState);
	Entity::RegisterLua(LuaManager::LuaState);
}

//void Game::CreatePlayer() {
//	//Player = &EntityManager->AddEntity();
//	Player->AddComponent<PositionComponent>(16, 16);
//	Player->AddComponent<SpriteComponent>(AssetManager::GetSpriteSheet("Player0"), 2, 1);
//	Player->AddComponent<BoxColliderComponent>();
//	Player->AddComponent<PhysicsComponent>();
//	Player->AddComponent<ControlMovementComponent>();
//	Player->AddGroup("Sprite");
//}

void Game::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			_isRunning = false;
			break;
		default:
			break;
	}
}

void Game::Update() 
{
	//_cnt++;
	EntityManager->Refresh();
	try
	{
		luabridge::LuaRef::getGlobal(LuaManager::LuaState, "Update")();
	}
	catch (const luabridge::LuaException & e)
	{
		cout << "LUA UPDATE ERROR.. " << e.what() << endl;
		//_isRunning = false;
	}
	EntityManager->Update();
	ViewPort->Update();
	//cout << _cnt << endl;
}

void Game::Render() 
{
	SDL_RenderClear(Renderer);
	SDL_SetRenderDrawColor(Renderer, 255, 0, 255, 255);
	EntityManager->Render();
	SDL_RenderPresent(Renderer);
}

void Game::Destroy()
{
	try
	{
		luabridge::LuaRef::getGlobal(LuaManager::LuaState, "Destroy")();
	}
	catch (const luabridge::LuaException & e)
	{
		cout << "LUA DESTORY ERROR.. " << e.what() << endl;
	}
	LuaManager::Destroy();
	SDL_DestroyWindow(Window);
	SDL_DestroyRenderer(Renderer);
	SDL_Quit();
	cout << "GAME DESTROYED..." << endl;
}

bool Game::IsRunning()
{
	return _isRunning;
}

