/// Representa a la plataforma del juego

#pragma once
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Paddle
{
private:
	Vector2D absolutePos_ = Vector2D(0, 0),
		dir_ = Vector2D(1, 0),
		vel_ = Vector2D(1, 0);
	uint width_ = 0,
		height_ = 0;
	Texture* texture_ = nullptr;

public:
	Paddle() {}
	Paddle(Vector2D absolutePos, uint width, uint height, Texture* texture) :
		absolutePos_(absolutePos), width_(width), height_(height), texture_(texture) {}
	Paddle(Vector2D absolutePos, uint width, uint height, Texture* texture, Vector2D vel) :
		absolutePos_(absolutePos), width_(width), height_(height), texture_(texture), vel_(vel) {}
	~Paddle() {}

	// Dibuja en pantalla el estado actual
	void render();
	// Actualiza, moviendose en relacion a su direccion y velocidad
	void update();
	// Trata los eventos de teclado
	void handleEvents(SDL_Event & event);
	// Determina el vector de colision con la pelota
	///Vector2D collides();
};