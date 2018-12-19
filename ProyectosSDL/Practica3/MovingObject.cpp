#include "MovingObject.h"

MovingObject::MovingObject() :
	ArkanoidObject(), dir_(Vector2D()), vel_(Vector2D()), speed_(0)
{
}

MovingObject::MovingObject(Texture * t, Vector2D p, Vector2D d, Vector2D v, uint s, double w, double h) :
	ArkanoidObject(t, p, w, h), dir_(d), vel_(v), speed_(s)
{
}

void MovingObject::update()
{
	vel_ = dir_ * speed_;
	pos_ = pos_ + vel_;
}

void MovingObject::loadFromFile(std::ifstream & file)
{
	ArkanoidObject::loadFromFile(file);
	double x, y;
	file >> x >> y;
	dir_ = Vector2D(x, y);
	file >> x >> y;
	vel_ = Vector2D(x, y);
	file >> speed_;
}

void MovingObject::saveToFile(std::ofstream & file)
{
	ArkanoidObject::saveToFile(file);
	file << dir_ << "\n" << vel_ << "\n" << speed_ << "\n";
}
