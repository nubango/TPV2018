#include "Wall.h"

void Wall::render() const
{
	SDL_Rect destRect = { absolutePos_.getX(),absolutePos_.getY(),width_,height_ };
	texture_->render(destRect);
}