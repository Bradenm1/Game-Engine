#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* fileName)
{
	SDL_Surface* _tempSurface = LoadSurface(fileName);
	SDL_Texture* _tex = SDL_CreateTextureFromSurface(Game::Renderer, _tempSurface);
	SDL_FreeSurface(_tempSurface);
	
	return _tex;
}

SDL_Surface* TextureManager::LoadSurface(const char* fileName)
{
	return IMG_Load(fileName);
}