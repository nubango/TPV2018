#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Game; // Por la inclusion circular

class Ball
{
private:
	Vector2D pos_ = Vector2D(0, 0),
		dir_ = Vector2D(0, 0),
		vel_ = Vector2D(0, 0);
	uint width_ = 0,
		height_ = 0;

	int speed_ = 0;

	Texture* texture_ = nullptr;
	Game* game_ = nullptr;

public:
	Ball(Vector2D pos, uint width, uint height, Texture* texture, Game* game);
	~Ball() {}

	// Gets
	Vector2D getVel() { return dir_; };
	Vector2D getPos() { return pos_; };

	// Devuelve el SDL_Rect de la bola
	SDL_Rect getDestRect() { return { (int)pos_.getX(), (int)pos_.getY(), (int)width_, (int)height_ }; }

	// Comprueba si la bola esta fuera del mapa
	bool isOutOfBounds();
	// Devuelve la bola a su estado inicial
	void reset();

	// Dibuja en pantalla el estado actual de la bola
	void render();
	// Se actualiza segun su velocidad y direccion, y si rebota dependiendo del vector de rebote
	void update();
};