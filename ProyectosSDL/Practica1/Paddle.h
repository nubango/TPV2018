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

	double velocity = 10;

public:
	Paddle(Vector2D pos, uint width, uint height, Texture* texture);
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