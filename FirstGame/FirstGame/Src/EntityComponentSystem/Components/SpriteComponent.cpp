#include "SpriteComponent.h"

SpriteComponent::SpriteComponent()
{
}

SpriteComponent::SpriteComponent(SpriteSheet* spriteSheet)
{
	_spriteSheet = spriteSheet;
}

SpriteComponent::SpriteComponent(SpriteSheet* spriteSheet, int x = 0, int y = 0)
{
	_spriteSheet = spriteSheet;
	SetSpiteSourceRenderSize(SPRITESIZE, SPRITESIZE);
	SetSpiteSourceRender(x, y);
}

void SpriteComponent::SetSpriteSheet(SpriteSheet* spriteSheet) 
{
	_spriteSheet = spriteSheet;
	SetSpiteSourceRenderSize(SPRITESIZE, SPRITESIZE);
	SetSpiteSourceRender(0 * srcRect.h, 0 * srcRect.w);
}

void SpriteComponent::SetSpriteSheet(SpriteSheet* spriteSheet, int x = 0, int y = 0)
{
	_spriteSheet = spriteSheet;
	SetSpiteSourceRenderSize(SPRITESIZE, SPRITESIZE);
	SetSpiteSourceRender(x, y);
}

void SpriteComponent::SetSpiteSourceRender(int x, int y)
{
	srcRect.x = x * srcRect.h;
	srcRect.y = y * srcRect.w;
}

void SpriteComponent::SetSpiteSourceRenderSize(int w, int h)
{
	srcRect.h = w;
	srcRect.w = h;
}

void SpriteComponent::Init()
{
	_position = &entity->GetComponent<PositionComponent>();
}

void SpriteComponent::Update()
{
	destRect.x = _position->GetX() - Game::ViewPort->Viewport.x;
	destRect.y = _position->GetY() - Game::ViewPort->Viewport.y;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
}

void SpriteComponent::Render()
{
	_spriteSheet->Render(srcRect, destRect);
}

SpriteComponent::~SpriteComponent()
{
	delete &destRect;
	delete &srcRect;
}

void SpriteComponent::Lua_SetSpriteSheet(SpriteSheet* spriteSheet, int x, int y)
{
	SetSpriteSheet(spriteSheet, x, y);
}
