#include "Paddle.h"
#include "Texture.h"

void Paddle::render()
{
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,height_ };
	texture_->render(destRect);
}

void Paddle::update()
{
	Vector2D nextPos;
	nextPos = pos_ + vel_;

	pos_ = nextPos;
}

void Paddle::handleEvents(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_RIGHT)
			vel_.setX(velocity);
		if (event.key.keysym.sym == SDLK_LEFT)
			vel_.setX(-velocity);
	}
}

bool Paddle::collides(Vector2D & collVector)
{
	return false;
}
