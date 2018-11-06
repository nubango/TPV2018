#pragma once
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Game; // Por la inclusion circular

class Ball
{
private:
	int speed_ = 5;
	Vector2D pos_ = Vector2D(0, 0),
		dir_ = Vector2D(1, -1),
		vel_ = Vector2D(1, -1);
	uint width_ = 0,
		height_ = 0;

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

	// Dibuja en pantalla el estado actual de la bola
	void render();
	// Se actualiza segun su velocidad y direccion, y si rebota dependiendo del vector de rebote
	void update();
};