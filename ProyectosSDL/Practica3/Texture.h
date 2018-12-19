#pragma once

#include "Font.h"

class Texture
{
private:
	SDL_Texture* texture_;
	SDL_Renderer* renderer_;

	uint width_;
	uint height_;
	uint numCols_;
	uint numRows_;
	uint frameWidth_;
	uint frameHeight_;

public:
	Texture(SDL_Renderer* r = nullptr);
	Texture(SDL_Renderer* r, std::string filename, uint numRows = 1, uint numCols = 1);
	~Texture();

	int getWidth() const { return width_; };
	int getHeight() const { return height_; };
	uint getNumRows() const { return numRows_; };
	uint getNumCols() const { return numCols_; };
	uint getFrameWidth() const { return frameWidth_; };
	uint getFrameHeight() const { return frameHeight_; };
	SDL_Texture* getTexture() const { return texture_; };

	void load(std::string filename, uint numRows = 1, uint numCols = 1);
	void loadFont(std::string text, const Font * font, const SDL_Color colour);
	void render(const SDL_Rect& destRect, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, uint row, uint col, double angle = 0.0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

private:
	void clean();
};

