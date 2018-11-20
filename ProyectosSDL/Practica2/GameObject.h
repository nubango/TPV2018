#pragma once
#include "checkML.h"
#include "SDL.h"
#include "SDL_image.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void handleEvent(SDL_Event & event) = 0;
};