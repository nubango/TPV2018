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

	virtual void loadFromFile(string const& filename) {}
	virtual void saveToFile() {}
};