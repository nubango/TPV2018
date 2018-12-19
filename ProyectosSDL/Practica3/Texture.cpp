#include "Texture.h"

Texture::Texture(SDL_Renderer * r) :
	renderer_(r), width_(0), height_(0), numCols_(0), numRows_(0), frameHeight_(0), frameWidth_(0)
{
}

Texture::Texture(SDL_Renderer * r, std::string filename, uint numRows, uint numCols) :
	renderer_(r)
{
	load(filename, numRows, numCols);
}

Texture::~Texture()
{
	clean();
}

void Texture::clean()
{
	if (texture_)
	{
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
		width_ = height_ = 0;
		numRows_ = numCols_ = 1;
		frameWidth_ = frameHeight_ = 0;
	}
}

void Texture::load(std::string filename, uint numRows, uint numCols)
{
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());
	if (!tempSurface) return;

	clean();
	texture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
	if (!texture_) return;

	numRows_ = numRows;
	numCols_ = numCols;
	width_ = tempSurface->w;
	height_ = tempSurface->h;
	frameWidth_ = width_ / numCols_;
	frameHeight_ = height_ / numRows_;

	SDL_FreeSurface(tempSurface);
}

void Texture::loadFont(std::string text, const Font * font, const SDL_Color color)
{
	SDL_Surface* tempSurface = font->loadSurface(text, color);
	if (!tempSurface) return;

	clean();
	texture_ = SDL_CreateTextureFromSurface(renderer_, tempSurface);
	if (!texture_) return;

	numRows_ = 1;
	numCols_ = 1;
	width_ = tempSurface->w;
	height_ = tempSurface->h;
	frameWidth_ = width_ / numCols_;
	frameHeight_ = height_ / numRows_;

	SDL_FreeSurface(tempSurface);
}

void Texture::render(const SDL_Rect& destRect, double angle, SDL_RendererFlip flip) const
{
	SDL_RenderCopyEx(renderer_, texture_, NULL, &destRect, angle, 0, flip);
}

void Texture::renderFrame(const SDL_Rect& destRect, uint row, uint col, double angle, SDL_RendererFlip flip) const
{
	SDL_Rect srcRect = {
		(int)frameWidth_ * (int)col,
		(int)frameHeight_ * (int)row,
		(int)frameWidth_,
		(int)frameHeight_
	};

	SDL_RenderCopyEx(renderer_, texture_, &srcRect, &destRect, angle, 0, flip);
}