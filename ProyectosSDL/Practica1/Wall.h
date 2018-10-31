/// Representa los muros del juego

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

public:
	Wall() {};
	Wall(Vector2D pos, uint width, uint height, Texture* texture);
	~Wall() {};

	// Se dibuja el estado actual en pantalla
	void render() const;
	// Determina el vector de colision con la pelota
	bool collides(Vector2D & collVector);
};