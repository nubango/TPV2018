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
}

void ArkanoidObject::handleEvent(SDL_Event & event)
{
}