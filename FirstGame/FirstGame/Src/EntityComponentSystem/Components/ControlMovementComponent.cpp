#include "ControlMovementComponent.h"

ControlMovementComponent::ControlMovementComponent()
{
}

void ControlMovementComponent::Init()
{
    _position = &entity->GetComponent<PositionComponent>();
    _physics = &entity->GetComponent<PhysicsComponent>();
}

void ControlMovementComponent::Update()
{
    SDL_PollEvent(&_event);
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    if (keystates[SDL_SCANCODE_UP] && !entity->CollisionDirection.test(3)) {
        _physics->Velocity->y = -entity->MovementSpeed;
    }
    if (keystates[SDL_SCANCODE_DOWN] && !entity->CollisionDirection.test(2)) {
        _physics->Velocity->y = entity->MovementSpeed;
    }
    if (keystates[SDL_SCANCODE_LEFT] && !entity->CollisionDirection.test(1)) {
        _physics->Velocity->x = -entity->MovementSpeed;
    }
    if (keystates[SDL_SCANCODE_RIGHT] && !entity->CollisionDirection.test(0)) {
        _physics->Velocity->x = entity->MovementSpeed;
    }
}

ControlMovementComponent::~ControlMovementComponent()
{
    delete &_event;
}
