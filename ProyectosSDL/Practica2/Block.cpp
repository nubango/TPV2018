#include "Block.h"
#include "Game.h"

Block::Block() : 
	ArkanoidObject(), color_(0), row_(0), col_(0)
{
}

Block::Block(Vector2D pos, uint width, uint height, uint color, uint row, uint col, Texture * texture) :
	ArkanoidObject(pos, width, height, texture), color_(color), row_(row), col_(col)
{
}

Block::~Block()
{
}

void Block::render() const
{
	// Conseguimos la fila en la que esta el color
	int row = 0;
	if (color_ < 3) row = 0;
	else row = 1;

	// Conseguimos la columna en la que esta el color
	int col = 0;
	if (color_ < 3) col = color_;
	else col = color_ % texture_->getNumCols();

	// destRect = {x, y, w, h}
	SDL_Rect destRect = { WALL_SIZE + col_ * width_, WALL_SIZE + row_ * height_, width_, height_ };
	texture_->renderFrame(destRect, row, col);
}