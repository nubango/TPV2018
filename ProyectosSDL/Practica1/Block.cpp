#include "Block.h"
#include "Game.h"

void Block::render()
{
	int row = 0;
	if (color_ < 3) row = 0;
	else row = 1;

	int col = 0;
	if (color_ < 3) col = color_;
	else col = color_ % texture_->getNumCols();

	SDL_Rect destRect = { WALL_WIDTH + col_ * width_, WALL_WIDTH + row_ * height_, width_, height_ }; // {x, y, w, h}
	texture_->renderFrame(destRect, row, col);
}