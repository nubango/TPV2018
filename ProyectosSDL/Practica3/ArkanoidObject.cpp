#include "ArkanoidObject.h"


ArkanoidObject::ArkanoidObject() :
	GameObject(), texture_(nullptr), pos_(Vector2D()), width_(0.0), height_(0.0)
{
}

ArkanoidObject::ArkanoidObject(Texture * t, Vector2D p, double w, double h) :
	GameObject(), texture_(t), pos_(p), width_(w), height_(h)
{
}

void ArkanoidObject::setInitialState()
{
}

bool ArkanoidObject::collides(const SDL_Rect & rect, const Vector2D & vel, Vector2D & collVector)
{
	return SDL_HasIntersection(&getRect(), &rect);
}

bool ArkanoidObject::handleEvent(const SDL_Event& event)
{
	return false;
}

void ArkanoidObject::update()
{
	return;
}

void ArkanoidObject::render()
{
	texture_->render(getRect());
}

void ArkanoidObject::loadFromFile(std::ifstream & file)
{
	double x, y;
	file >> x >> y >> width_ >> height_;
	pos_ = Vector2D(x, y);
}

void ArkanoidObject::saveToFile(std::ofstream & file)
{
	file << pos_ << "\n" << width_ << " " << height_ << "\n";
}

SDL_Rect ArkanoidObject::getRect()
{
	SDL_Rect rect = { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ };
	return rect;
}