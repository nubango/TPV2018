#include "Ball.h"
#include "Game.h" // Por la inclusion circular

Ball::Ball(Vector2D pos, uint width, uint height, Texture * texture, Game * game) :
	pos_(pos), width_(width), height_(height), texture_(texture), game_(game)
{
	speed_ = 2;
	dir_ = { 1,-1 };
	vel_ = dir_ * speed_;
}

bool Ball::isOutOfBounds()
{
	if (pos_.getY() > WIN_HEIGHT)
		return true;
	else
		return false;
}

void Ball::reset()
{
	speed_ = 2;
	dir_ = { 1,-1 };
	vel_ = dir_ * speed_;

	pos_ = { WIN_WIDTH / 2,WIN_HEIGHT - 30 };
}

void Ball::render()
{
	SDL_Rect destRect = getDestRect();
	texture_->render(destRect);
}

void Ball::update()
{
	// Comprobamos el choque con la posicions siguiente
	Vector2D nextPos = pos_ + vel_;
	SDL_Rect ballRect = { nextPos.getX(), nextPos.getY(), width_, height_ };

	Vector2D collVector = vel_;
	// collVector es el vector perpendicular del objeto contra el que choca
	if (game_->collides(ballRect, dir_, collVector))
	{
		collVector.normalize();
		// Aplicamos la reflexion
		dir_ = dir_ - collVector * (2.0 * (dir_*collVector));
	}

	vel_ = dir_ * speed_;
	// Movemos la bola
	pos_ = pos_ + vel_;

	//--------------------------------------------------------------------------------------

	//SDL_Rect ballRect = getDestRect();
	//Vector2D collVector = vel_;

	//// collVector es el vector perpendicular del objeto contra el que choca
	//if (game_->collides(ballRect, dir_, collVector))
	//{
	//	collVector.normalize();
	//	// Aplicamos la reflexion
	//	dir_ = dir_ - collVector * (2.0 * (dir_*collVector));
	//}

	//vel_ = dir_ * speed_;
	//// Movemos la bola
	//pos_ = pos_ + vel_;
}