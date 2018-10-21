#include "Block.h"



void Block::colorAbsolutePosition(uint color)
{
	/*switch (color) {
	case 1:
		absolutePos_ = { 0,0 };
		break;
	case 2:
		absolutePos_ = { 0,0 };
		break;
	case 3:
		absolutePos_ = { 0,0 };
		break;
	case 4:
		absolutePos_ = { 0,0 };
		break;
	case 5:
		absolutePos_ = { 0,0 };
		break;
	case 6: 
		absolutePos_ = { 0,0 };
		break;
	default:
		break;
	}*/
}

void Block::render()
{
	SDL_Rect destRect = { absolutePos_.getX(), absolutePos_.getY(),width_,height_ };
	texture_->renderFrame(destRect, row_, col_);
}