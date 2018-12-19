#pragma once
#include "GameState.h"
#include "Wall.h"

class PlayState :
	public GameState
{
public:
	PlayState();
	PlayState(Game* game);
	virtual ~PlayState();

	virtual bool handleEvent(const SDL_Event& e);
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
};