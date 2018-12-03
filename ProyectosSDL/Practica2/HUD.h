#pragma once
#include "ArkanoidObject.h"

class Game;

class HUD:
	public ArkanoidObject
{
protected:
	Texture* logoTexture_;
	Texture* livesTexture_;

	Game* game_;

	uint numLives_;

public:
	HUD();
	HUD(Vector2D pos, uint width, uint height, Texture* texture);
	virtual ~HUD();

	virtual void render();
};