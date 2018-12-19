#pragma once
#include "GameState.h"
class EndState :
	public GameState
{
public:
	EndState();
	EndState(Game* game);
	virtual ~EndState();

	virtual bool handleEvent(const SDL_Event& e);
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();
};