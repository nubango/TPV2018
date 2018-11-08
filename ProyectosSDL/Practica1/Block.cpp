#include "Block.h"
#include "Game.h"

Block::Block(uint color, uint row, uint col, Texture * texture) :
	color_(color), row_(row), col_(col), texture_(texture)
{
	pos_.setX(col);
	pos_.setY(row);
}

void Block::render()
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
	SDL_Rect destRect = { WALL_WIDTH + col_ * width_, WALL_WIDTH + row_ * height_, width_, height_ };
	texture_->renderFrame(destRect, row, col);
}