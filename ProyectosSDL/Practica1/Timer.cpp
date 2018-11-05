#include "Timer.h"

Timer::Timer(Vector2D pos, uint width, uint height, Texture* texture) :
	pos_(pos), width_(width), height_(height), texture_(texture)
{
}

Timer::~Timer()
{
}

void Timer::render()
{
	SDL_Rect destRect = { pos_.getX(), pos_.getY(), width_ / texture_->getNumCols(), height_ };
	texture_->renderFrame(destRect, 0, 0);
	destRect = { (int)pos_.getX() + (int)width_ / (int)texture_->getNumCols(), (int)pos_.getY(), (int)width_ / (int)texture_->getNumCols(), (int)height_ };
	texture_->renderFrame(destRect, 0, 1);
}

void Timer::update()
{
}