#include "MovingObject.h"

MovingObject::MovingObject() : 
	ArkanoidObject(), dir_(0, 0), vel_(0, 0), speed_(0)
{
}

MovingObject::MovingObject(Vector2D pos, Vector2D dir, double speed, uint width, uint height, Texture * texture) : 
	ArkanoidObject(pos, width, height, texture), dir_(dir), speed_(speed)
{
	vel_ = dir_ * speed_;
}

MovingObject::~MovingObject()
{
}

void MovingObject::loadFromFile(string const& filename)
{
}

void MovingObject::saveToFile()
{
}