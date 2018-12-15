#include "ArkanoidObject.h"

ArkanoidObject::ArkanoidObject() :
	GameObject(), pos_(0, 0), width_(0), height_(0), texture_(nullptr)
{
}

ArkanoidObject::ArkanoidObject(Vector2D pos, double width, double height, Texture * texture) :
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
	// SDL_HasIntersection comprueba si hay colision entre dos SDL_Rects
	return SDL_HasIntersection(&getRect(), &rect);
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
	file << pos_ << " " << width_ << " " << height_;
}