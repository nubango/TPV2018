#include "ArkanoidObject.h"

ArkanoidObject::ArkanoidObject() : 
	GameObject(), pos_(0, 0), width_(0), height_(0)
{
}

ArkanoidObject::ArkanoidObject(Vector2D pos, uint width, uint height, Texture * texture) : 
	GameObject(), pos_(pos), width_(width), height_(height), texture_(texture)
{
}

ArkanoidObject::~ArkanoidObject()
{
}

void ArkanoidObject::render() const
{
	texture_->render(getRect());
}

void ArkanoidObject::update()
{
	// Por defecto no hacen nada (sirve para los bucles de los updates de todos los objetos)
}

void ArkanoidObject::handleEvent(SDL_Event & event)
{
	// Por defecto no hacen nada (sirve para los bucles de los updates de todos los objetos)
}

bool ArkanoidObject::collides(const SDL_Rect & rect, const Vector2D & vel, Vector2D & collVector)
{
	return false;
}

void ArkanoidObject::loadFromFile(ifstream & file)
{
	// file >> pos_ >> width_ >> height_;

	double x, y;
	file >> x >> y;
	pos_.setXY(x, y);
	file >> width_ >> height_;
}

void ArkanoidObject::saveToFile(ofstream & file)
{
	file << pos_ << width_ << height_;
}