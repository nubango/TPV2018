#include "Wall.h"

Wall::Wall(Vector2D pos, uint width, uint height, Vector2D normal, Texture * texture) :
	pos_(pos), width_(width), height_(height), normal_(normal), texture_(texture)
{
}

void Wall::render() const
{
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,height_ };
	texture_->render(destRect);
}

bool Wall::collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector)
{
	// SDL_HasIntersection comprueba si hay colision entre dos SDL_Rects
	if (SDL_HasIntersection(&rect, &getDestRect()))
	{
		// Pared superior
		if (normal_.getX() == 0 && normal_.getY() == 1)
			collVector = Vector2D(vel.getX(), -vel.getY());
		// Pared derecha e izquierda
		else if (normal_.getX() == 1, normal_.getY() == 0)
			collVector = Vector2D(-vel.getX(), vel.getY());
		return true;
	}
	return false;
}