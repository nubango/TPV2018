#include "Wall.h"

Wall::Wall(Vector2D pos, uint width, uint height, Texture * texture) :
	pos_(pos), width_(width), height_(height), texture_(texture)
{
	perpendicular_ = { pos_.getY(), -pos_.getX() };
}

void Wall::render() const
{
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,height_ };
	texture_->render(destRect);
}

bool Wall::collides(Vector2D & collVector)
{
	collVector = perpendicular_;
	return true;
}