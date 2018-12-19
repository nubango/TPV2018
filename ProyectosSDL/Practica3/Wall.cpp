#include "Wall.h"

Wall::Wall() : 
	ArkanoidObject(), normal_(Vector2D())
{
}

Wall::Wall(Texture * t, Vector2D p, Vector2D n, double w, double h) :
	ArkanoidObject(t, p, w, h), normal_(n)
{
}

Wall::~Wall()
{
}

bool Wall::collides(const SDL_Rect & rect, const Vector2D & vel, Vector2D & collVector)
{
	if (ArkanoidObject::collides(rect, vel, collVector))
	{
		collVector = normal_;
		return true;
	}
	return false;
}

void Wall::loadFromFile(std::ifstream & file)
{
	ArkanoidObject::loadFromFile(file);
	double x, y;
	file >> x >> y;
	normal_ = Vector2D(x, y);
}

void Wall::saveToFile(std::ofstream & file)
{
	ArkanoidObject::saveToFile(file);
	file << normal_ << "\n";
}
