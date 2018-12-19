#pragma once

#include "ArkanoidObject.h"

class Wall : public ArkanoidObject
{
private:
	Vector2D normal_;

public:
	Wall();
	Wall(Texture* t, Vector2D p, Vector2D n, double w, double h);
	virtual ~Wall();

	virtual bool collides(const SDL_Rect& rect, const Vector2D& vel, Vector2D& collVector);
	virtual void loadFromFile(std::ifstream& file);
	virtual void saveToFile(std::ofstream& file);
};

