#pragma once
#include <SDL_ttf.h>
#include <string>

class Font
{
private:
	TTF_Font* font_;

public:
	Font();
	Font(std::string filename, int size);
	~Font();

	void load(std::string filename, int size);
	SDL_Surface* loadSurface(std::string text, SDL_Color color) const;
	void freeFont();
};