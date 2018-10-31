/// Representa a la plataforma del juego

#pragma once
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Paddle
{
private:
	Vector2D pos_ = Vector2D(0, 0),
		vel_ = Vector2D(velocity, 0);
	uint width_ = 0,
		height_ = 0;

	Texture* texture_ = nullptr;

	double velocity = 5;

public:
	Paddle() {}
	Paddle(Vector2D absolutePos, uint width, uint height, Texture* texture) :
		pos_(absolutePos), width_(width), height_(height), texture_(texture) {}
	Paddle(Vector2D absolutePos, uint width, uint height, Texture* texture, Vector2D vel) :
		pos_(absolutePos), width_(width), height_(height), texture_(texture), vel_(vel) {}
	~Paddle() {}

	// Dibuja en pantalla el estado actual
	void render();
	// Actualiza, moviendose en relacion a su direccion y velocidad
	void update();
	// Trata los eventos de teclado
	void handleEvents(SDL_Event & event);
	// Determina el vector de colision con la pelota
	bool collides(Vector2D & collVector);
};