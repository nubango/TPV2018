/// Representa la pelota del juego

#pragma once
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Game;

class Ball
{
private:
	Vector2D absolutePos_ = Vector2D(0, 0),
		dir_ = Vector2D(1, 0),
		vel_ = Vector2D(1, 0);
	uint width_ = 0,
		height_ = 0;
	Texture* texture_ = nullptr;
	Game* game_ = nullptr;

public:
	Ball() {}
	Ball(Vector2D absolutePos, uint width, uint height, Texture* texture, Game* game) :
		absolutePos_(absolutePos), width_(width), height_(height), texture_(texture), game_(game) {}
	Ball(Vector2D absolutePos, uint width, uint height, Texture* texture, Game* game, Vector2D vel) :
		absolutePos_(absolutePos), width_(width), height_(height), texture_(texture), game_(game), vel_(vel) {}
	~Ball() {}

	// Dibuja en pantalla el estado actual de la bola
	void render();
	// Se actualiza segun su velocidad y direccion, y si rebota dependiendo del vector de rebote
	void update();
};