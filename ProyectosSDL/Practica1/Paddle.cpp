#include "Paddle.h"
#include "Game.h" // Para acceder a la variables constantes

Paddle::Paddle(Vector2D pos, uint width, uint height, Texture * texture) :
	pos_(pos), width_(width), height_(height), texture_(texture)
{
}

void Paddle::render()
{
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,height_ };
	texture_->render(destRect);
}

void Paddle::update()
{
	Vector2D nextPos;
	nextPos = pos_ + vel_;
	// Solo se mueve si la siguiente posicion es valida
	if (nextPos.getX() > WALL_WIDTH && nextPos.getX() < WIN_WIDTH - WALL_WIDTH - width_)
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
	if (event.type == SDL_KEYUP)
		vel_.setX(0);
}

bool Paddle::collides(Vector2D & collVector)
{
	// collVector contra el paddle es distinto, depende de la zona donde colisione
	collVector = { pos_.getY(), -pos_.getX() };
	return false;
}