#include "Font.h"

Font::Font(std::string filename, uint fontSize) :
	font_(nullptr), size_(fontSize)
{
	load(filename, fontSize);
}

Font::~Font()
{
	clean();
}

void Font::load(std::string filename, uint fontSize)
{
	font_ = TTF_OpenFont(filename.c_str(), fontSize);
}

SDL_Surface * Font::loadSurface(std::string text, SDL_Color colour) const
{
	if (font_) return TTF_RenderText_Solid(font_, text.c_str(), colour);
	else return nullptr;
}

void Font::clean()
{
	if (font_)
	{
		TTF_CloseFont(font_);
		font_ = nullptr;
		size_ = 0;
	}
}
