#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Timer
{
private:
	Vector2D pos_ = Vector2D(0, 0);
	uint width_ = 0,
		height_ = 0;
	Texture* texture_ = nullptr;

	uint seconds_ = 0;

public:
	Timer(Vector2D pos, uint width, uint height, Texture* texture);
	~Timer();

	// Dibuja en pantalla el temporizador
	void render();
	// Se actualiza el temporizador
	void update();

	void startTimer();

	void resetTimer();
};