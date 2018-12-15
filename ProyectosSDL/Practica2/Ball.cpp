#include "Ball.h"
#include "Game.h"

Ball::Ball() :
	MovingObject()
{
}

Ball::Ball(Vector2D pos, Vector2D dir, double speed, double width, double height, Texture * texture, Game* game) :
	MovingObject(pos, dir, speed, width, height, texture), game_(game)
{
}

Ball::~Ball()
{
}

void Ball::update()
{
	collVector_ = dir_;
	// collVector es el vector perpendicular del objeto contra el que choca
	if (game_->collides(getRect(), dir_, collVector_))
	{
		collVector_.normalize();
		// Aplicamos la reflexion
		dir_ = dir_ - collVector_ * (2.0 * (dir_*collVector_));

		std::cout << collVector_; 
	}
	// Movemos la bola
	MovingObject::update();
}

void Ball::handleEvent(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
 			dir_.setY(-1);
			dir_.setX(-1);
		}
	}
}