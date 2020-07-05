#include "SpriteSheet.h"
#include "TextureManager.h" 

SpriteSheet::SpriteSheet()
{
}

SpriteSheet::SpriteSheet(const char* spriteSheetLocation)
{
	_spriteSheet = TextureManager::LoadTexture(spriteSheetLocation);
}

void SpriteSheet::Render(SDL_Rect srcRect, SDL_FRect destRect)
{
	SDL_RenderCopyF(Game::Renderer, _spriteSheet, &srcRect, &destRect);
}

SpriteSheet::~SpriteSheet()
{
	delete _spriteSheet;
}
