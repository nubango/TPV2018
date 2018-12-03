#include "Wall.h"

Wall::Wall() :
	ArkanoidObject(), normal_(0, 0)
{
}

Wall::Wall(Vector2D pos, uint width, uint height, Vector2D normal, Texture * texture) :
	ArkanoidObject(pos, width, height, texture), normal_(normal)
{
}

Wall::~Wall()
{
}

bool Wall::collides(const SDL_Rect & rect, const Vector2D & vel, Vector2D & collVector)
{
	// SDL_HasIntersection comprueba si hay colision entre dos SDL_Rects
	if (SDL_HasIntersection(&rect, &getRect()))
	{
		collVector = normal_;
		return true;
	}
	return false;
}

void Wall::loadFromFile(ifstream & file)
{
	ArkanoidObject::loadFromFile(file);
	double x, y;
	file >> x >> y;
	normal_.setXY(x, y);
}

void Wall::saveToFile(ofstream & file)
{
	ArkanoidObject::saveToFile(file);
	file << normal_;
}