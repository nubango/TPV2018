#pragma once
#include "ArkanoidObject.h"

class Wall :
	public ArkanoidObject
{
protected:
	Vector2D normal_;

public:
	Wall();
	Wall(Vector2D pos, uint width, uint height, Vector2D normal, Texture* texture);
	virtual ~Wall();

	virtual bool collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector);
	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
};