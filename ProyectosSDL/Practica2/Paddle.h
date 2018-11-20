#pragma once
#include "MovingObject.h"

class Paddle :
	public MovingObject
{
public:
	Paddle();
	Paddle(Vector2D pos, Vector2D dir, double speed, uint width, uint height, Texture * texture);
	virtual ~Paddle();

	virtual void render();
	virtual void update();
	virtual void handleEvent(SDL_Event & event);

	virtual void loadFromFile(string const& filename);
	virtual void saveToFile();
};