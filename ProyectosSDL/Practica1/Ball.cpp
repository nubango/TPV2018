#include "Ball.h"
#include "Game.h" // Por la inclusion circular

void Ball::render()
{
	SDL_Rect destRect = { absolutePos_.getX(),absolutePos_.getY(),width_,height_ };
	texture_->render(destRect);
}

void Ball::update()
{
	//absolutePos_.getX() += vel_.getX() * dir_.getX();
	//absolutePos_.getY() += vel_.getY() * dir_.getY();
	Vector2D collider;
	if (game_->collides(collider)); // devuelve el vector contra el que colisiona;
}