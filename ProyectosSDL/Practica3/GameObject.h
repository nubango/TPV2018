#pragma once

#include "Vector2D.h"
#include "Texture.h"

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};

	virtual bool handleEvent(const SDL_Event& event) = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};