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

void MovingObject::loadFromFile(ifstream & file)
{
	double x, y;
	file >> x >> y;
	dir_.setXY(x, y);
	file >> speed_;

	// vel_ = dir_ * speed_;
}

void MovingObject::saveToFile(ofstream& file)
{
	file << dir_ << speed_;
}