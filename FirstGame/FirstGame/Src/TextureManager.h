#pragma once

#ifndef TEXTUREMANAGER_H // #include guards
#define TEXTUREMANAGER_H

#include "Game.hpp"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static SDL_Surface* LoadSurface(const char* fileName);
};

#endif