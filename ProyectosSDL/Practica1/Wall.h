/// Representa los muros del juego

#pragma once
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Wall
{
private:
	Vector2D absolutePos_ = { 0,0 };
	uint width_ = 0,
		height_ = 0;
	Texture* texture_ = nullptr;

public:
	Wall() {};
	Wall(Vector2D absolutePos, uint width, uint height, Texture* texture) :
		absolutePos_(absolutePos), width_(width), height_(height), texture_(texture) {};
	~Wall() {};

	// Se dibuja el estado actual en pantalla
	void render() const;
};