#include "Paddle.h"
#include "Texture.h"

void Paddle::render()
{
	SDL_Rect destRect = { absolutePos_.getX(),absolutePos_.getY(),width_,height_ };
	texture_->render(destRect);
}

void Paddle::update()
{
	//absolutePos_.getX() = absolutePos_.getX + (vel_.getX() * vel_.getX());
	//absolutePos_  = absolutePos_ + (vel_ * dir_);
}

void Paddle::handleEvents(SDL_Event & event)
{
	if (event.type == SDLK_RIGHT)
		dir_.setX(1.0);
	if (event.type == SDLK_LEFT)
		dir_.setX(-1.0);
}