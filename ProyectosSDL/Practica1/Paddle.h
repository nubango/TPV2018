#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Paddle
{
private:
	Vector2D pos_ = Vector2D(0, 0),
		dir_ = Vector2D(0, 0),
		vel_ = Vector2D(0, 0);
	uint width_ = 0,
		height_ = 0;

	Texture* texture_ = nullptr;

	double speed_ = 0;

	// Devuelve el SDL_Rect de la pala
	SDL_Rect getDestRect() { return { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

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
	bool collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector);
};