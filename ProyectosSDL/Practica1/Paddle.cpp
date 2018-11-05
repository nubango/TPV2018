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

bool Paddle::collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector)
{
	// SDL_HasIntersection comprueba si hay colision entre dos SDL_Rects
	// DestRect es la propia pala
	if (SDL_HasIntersection(&rect, &getDestRect()))
	{
		double midPoint = getDestRect().x + getDestRect().w / 2;
		// Si colisiona por el lado izquierdo
		if (rect.x < midPoint)
		{
			// Si viene del lado opuesto
			if (vel.getX() == -1)
				collVector = Vector2D(vel.getX(), -vel.getY());
			// Si viene del mismo lado
			else
				collVector = Vector2D(-vel.getX(), -vel.getY());
		}
		// Si colisiona por el lado derecho
		else
		{
			// Si viene del lado opuesto
			if (vel.getX() == -1)
				collVector = Vector2D(-vel.getX(), -vel.getY());
			// Si viene del mismo lado
			else
				collVector = Vector2D(vel.getX(), -vel.getY());
		}
		return true;
	}
	return false;
}