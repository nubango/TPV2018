#pragma once
#include "GameState.h"

class MenuState :
	public GameState
{
public:
	MenuState();
	MenuState(Game* game);
	virtual ~MenuState();

	virtual bool handleEvent(const SDL_Event& e);
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
};