#include "Ball.h"
#include "Game.h" // Por la inclusion circular

void Ball::render()
{
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,height_ };
	texture_->render(destRect);
}

void Ball::update()
{
	Vector2D prevPos = pos_;
	Vector2D collVector;
	SDL_Rect ballRect = getDestRect();
	// colVector es el vector perpendicular del objeto contra el que choca
	// colVector contra el paddle es distinto, depende de la zona donde colisione
	collVector.normalize();
	if (game_->collides(ballRect, vel_, collVector))
	{
		// Aplicamos la reflexion
		vel_ = vel_ - collVector * (2 * (vel_*collVector));
		pos_ = prevPos + vel_;
	}
}