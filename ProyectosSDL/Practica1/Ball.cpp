#include "Ball.h"
#include "Game.h" // Por la inclusion circular

Ball::Ball(Vector2D pos, uint width, uint height, Texture * texture, Game * game) :
	pos_(pos), width_(width), height_(height), texture_(texture), game_(game)
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
	Vector2D collVector = vel_;

	// collVector es el vector perpendicular del objeto contra el que choca
	if (game_->collides(ballRect, dir_, collVector))
	{
		// Aplicamos la reflexion
		collVector.normalize();
		dir_ = dir_ - collVector * (2 * (dir_*collVector));
		//dir_ = collVector;
	}

	vel_ = dir_ * speed_;
	// Movemos la bola
	pos_ = pos_ + vel_;
}