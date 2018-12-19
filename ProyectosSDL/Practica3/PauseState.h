#pragma once
#include "GameState.h"
class PauseState :
	public GameState
{
public:
	PauseState();
	PauseState(Game* game);
	virtual ~PauseState();

	virtual bool handleEvent(const SDL_Event& e);
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
};