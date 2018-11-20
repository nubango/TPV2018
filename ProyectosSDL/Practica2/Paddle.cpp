#include "Paddle.h"
#include "Game.h"

Paddle::Paddle() : 
	MovingObject()
{
}

Paddle::Paddle(Vector2D pos, Vector2D dir, double speed, uint width, uint height, Texture * texture) : 
	MovingObject(pos, dir, speed, width, height, texture)
{
}

Paddle::~Paddle()
{
}

void Paddle::render()
{
}

void Paddle::update()
{
	Vector2D nextPos;
	nextPos = pos_ + vel_;
	// Solo se mueve si la siguiente posicion es valida
	if (nextPos.getX() > WALL_SIZE && nextPos.getX() < WIN_WIDTH - WALL_SIZE - width_)
		pos_ = nextPos;
}

void Paddle::handleEvent(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_RIGHT)
			vel_.setX(speed_);
		if (event.key.keysym.sym == SDLK_LEFT)
			vel_.setX(-speed_);
	}
	if (event.type == SDL_KEYUP)
		vel_.setX(0);
}

void Paddle::loadFromFile(string const& filename)
{
}

void Paddle::saveToFile()
{
}