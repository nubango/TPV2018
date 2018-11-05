#pragma once
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Wall
{
private:
	Vector2D pos_ = { 0,0 };
	uint width_ = 0,
		height_ = 0;
	Texture* texture_ = nullptr;

	Vector2D normal_ = { 0,0 };

	// Devuelve el SDL_Rect de la pared
	SDL_Rect getDestRect() { return { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

public:
	Wall(Vector2D pos, uint width, uint height, Vector2D normal, Texture* texture);
	~Wall() {};

	// Se dibuja el estado actual en pantalla
	void render() const;
	// Determina el vector de colision con la pelota
	bool collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector);
};