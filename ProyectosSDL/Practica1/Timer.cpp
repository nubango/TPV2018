#include "Timer.h"

Timer::Timer(Vector2D pos, uint width, uint height, Texture* texture):
	pos_(pos), width_(width), height_(height), texture_(texture)
{
}

Timer::~Timer()
{
}

void Timer::render()
{
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,height_ };
	texture_->render(destRect);
}

void Timer::update()
{
}