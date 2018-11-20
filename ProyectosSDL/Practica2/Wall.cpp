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