#include "Texture.h"
#include <iostream>

using namespace std;

void Texture::clean() {
	SDL_DestroyTexture(texture_);
	texture_ = nullptr;
	width_ = height_ = 0;
}

void Texture::load(string filename, uint nRows, uint nCols) {
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (tempSurface == nullptr) throw "Error loading surface from " + filename;
	clean();
	texture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
	if (texture_ == nullptr) throw "Error loading texture from " + filename;
	numRows_ = nRows;
	numCols_ = nCols;
	width_ = tempSurface->w;
	height_ = tempSurface->h;
	frameWidth_ = width_ / numCols_;
	frameHeight_ = height_ / numRows_;
	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = width_; srcRect.h = height_;
	SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, 0, 0, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, int row, int col, int angle, SDL_RendererFlip flip) const {
	SDL_Rect srcRect;
	srcRect.x = frameWidth_ * col;
	srcRect.y = frameHeight_ * row;
	srcRect.w = frameWidth_;
	srcRect.h = frameHeight_;
	SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, angle, 0, flip);
}

void Texture::loadFont(std::string text, const Font * font, const SDL_Color color)
{
	SDL_Surface* surface = font->loadSurface(text, color);

	if (surface == nullptr)
		;// throw exception("Unable to render text surface: " + TTF_GetError());
	else
	{
		//free();

		texture_ = SDL_CreateTextureFromSurface(renderer_, surface);

		if (texture_ == nullptr)
		{
			;// throw exception("Unable to create texture from text: " + SDL_GetError());
			width_ = height_ = 0;
		}
		else
		{
			width_ = surface->w;
			height_ = surface->h;
			frameWidth_ = width_ / numCols_;
			frameHeight_ = height_ / numRows_;
		}

		SDL_FreeSurface(surface);
	}
}