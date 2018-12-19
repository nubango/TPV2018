#pragma once

#include "SDLIncludes.h"

class Font
{
private:
	TTF_Font* font_;
	uint size_;

public:
	Font() : font_(nullptr), size_(0) {};
	Font(std::string filename, uint fontSize);
	~Font();

	void load(std::string filename, uint fontSize);
	SDL_Surface* loadSurface(std::string text, SDL_Color colour) const;

private:
	void clean();
};

