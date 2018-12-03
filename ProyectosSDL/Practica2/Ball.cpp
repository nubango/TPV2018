#include "Ball.h"
#include "Game.h"

Ball::Ball() :
	MovingObject()
{
}

Ball::Ball(Vector2D pos, Vector2D dir, double speed, uint width, uint height, Texture * texture, Game* game) :
	MovingObject(pos, dir, speed, width, height, texture), game_(game)
{
}

Ball::~Ball()
{
}

void Ball::update()
{
	Vector2D collVector = vel_;
	// collVector es el vector perpendicular del objeto contra el que choca
	if (game_->collides(getRect(), dir_, collVector))
	{
		collVector.normalize();
		// Aplicamos la reflexion
		dir_ = dir_ - collVector * (2.0 * (dir_*collVector));
	}

	vel_ = dir_ * speed_;
	// Movemos la bola
	pos_ = pos_ + vel_;
}

void Ball::handleEvent(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
			dir_.setY(-1);
		//if (dir_.getY() != -1)
		//{
		//	if (event.key.keysym.sym == SDLK_RIGHT)
		//		dir_.setX(2);
		//	if (event.key.keysym.sym == SDLK_LEFT)
		//		dir_.setX(-2);
		//}
	}
	if (event.type == SDL_KEYUP)
		dir_.setX(0);
}