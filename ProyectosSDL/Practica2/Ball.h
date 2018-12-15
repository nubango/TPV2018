#pragma once
#include "MovingObject.h"

class Game;

class Ball :
	public MovingObject
{
protected:
	Game* game_;

	Vector2D collVector_;

public:
	Ball();
	Ball(Vector2D pos, Vector2D dir, double speed, double width, double height, Texture * texture, Game* game);
	virtual ~Ball();

	virtual void update();
	virtual void handleEvent(SDL_Event & event);
};