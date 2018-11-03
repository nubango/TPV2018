#include "Ball.h"
#include "Game.h" // Por la inclusion circular

Ball::Ball(Vector2D absolutePos, uint width, uint height, Texture * texture, Game * game) :
	pos_(absolutePos), width_(width), height_(height), texture_(texture), game_(game)
{
}

void Ball::render()
{
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,height_ };
	texture_->render(destRect);
}

void Ball::update()
{
	SDL_Rect ballRect = getDestRect();
	Vector2D prevPos = pos_;
	Vector2D collVector = { 0,0 };
	// collVector es el vector perpendicular del objeto contra el que choca
	if (game_->collides(ballRect, vel_, collVector))
	{
		collVector.normalize();
		// Aplicamos la reflexion
		vel_ = vel_ - collVector * (2 * (vel_*collVector));
		pos_ = prevPos + vel_;
	}
}