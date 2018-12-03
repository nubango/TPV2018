#include "Font.h"

Font::Font() : font_(nullptr)
{
}

Font::Font(std::string filename, int size) : font_(nullptr)
{
	load(filename, size);
}

Font::~Font()
{
	freeFont();
}

void Font::load(std::string filename, int size)
{
	font_ = TTF_OpenFont(filename.c_str(), size);
}

void Font::freeFont()
{
	if (font_ != nullptr) TTF_CloseFont(font_);
	font_ = nullptr;
}

SDL_Surface * Font::loadSurface(std::string text, SDL_Color color) const
{
	return TTF_RenderText_Solid(font_, text.c_str(), color);
}