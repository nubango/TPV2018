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
	virtual bool collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector);

	SDL_Rect getRect() const { return { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
};