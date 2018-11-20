#pragma once
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include <fstream>

class ArkanoidObject :
	public GameObject
{
protected:
	Vector2D pos_;
	uint width_,
		height_;

	Texture* texture_ = nullptr;

public:
	ArkanoidObject();
	ArkanoidObject(Vector2D pos, uint width, uint height, Texture* texture);
	virtual ~ArkanoidObject();

	virtual void render() const;
	virtual void update();
	virtual void handleEvent(SDL_Event & event);

	SDL_Rect getRect() const { return { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

	virtual void loadFromFile(string const& filename) = 0;
	virtual void saveToFile() = 0;
};