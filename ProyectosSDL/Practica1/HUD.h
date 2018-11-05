#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Timer.h"

typedef unsigned int uint;

class Game; // Por la inclusion circular

class HUD
{
private:
	Vector2D pos_ = Vector2D(0, 0);
	uint width_ = 0,
		height_ = 0;
	Texture* livesTexture_ = nullptr;
	Texture* logoTexture_ = nullptr;
	Texture* timerTexture_ = nullptr;
	Game* game_ = nullptr;
	Timer* timer_ = nullptr;

public:
	HUD(Vector2D pos, uint width, uint height, Texture * livesTexture, Texture* logoTexture, Texture* timerTexture, Game * game);
	~HUD();

	// Dibuja en pantalla el estado actual del HUD
	void render();
	// Se actualiza dependiendo del juego
	void update();
};