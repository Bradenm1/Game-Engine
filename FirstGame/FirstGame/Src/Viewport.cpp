#include "Viewport.h"

void ViewPort::Init(Entity* target)
{
	assert(target != NULL);
	TargetEntity = target;
	TargetEntityPosition = &TargetEntity->GetComponent<PositionComponent>();

	int win_width, win_height;
	SDL_GetWindowSize(Game::Window, &win_width, &win_height);
	Viewport.w = win_width / 2;
	Viewport.h = win_height / 2;
}

void ViewPort::Update()
{
	Viewport.x = TargetEntityPosition->GetX() - Viewport.w / 2;
	Viewport.y = TargetEntityPosition->GetY() - Viewport.h / 2;
}