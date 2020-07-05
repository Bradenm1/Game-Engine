#include "Game.hpp"

Game* _game = nullptr;

int main(int args, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint64 frameStart;
	int frameTime;
	
	_game = new Game();
	_game->EntityManager = new EntityManager();
	_game->TileMap = new TileMap();
	_game->ViewPort = new ViewPort();

	_game->Init("FirstGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (_game->IsRunning())
	{
		frameStart = SDL_GetTicks();

		_game->HandleEvents();
		_game->Update();
		_game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	_game->Destroy();
	return 0;
}