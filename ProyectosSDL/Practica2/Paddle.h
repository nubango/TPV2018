#pragma once
#include "MovingObject.h"

class Paddle :
	public MovingObject
{
public:
	Paddle();
	Paddle(Vector2D pos, Vector2D dir, double speed, uint width, uint height, Texture * texture);
	virtual ~Paddle();

	virtual void update();
	virtual void handleEvent(SDL_Event & event);
	virtual bool collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector);
	
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
};