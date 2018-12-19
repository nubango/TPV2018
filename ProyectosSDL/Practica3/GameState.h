#pragma once

#include "Button.h"

class Game;
class GameState
{
protected:
	Game* game_;
	std::list<GameObject*> stage_;

public:
	GameState();
	GameState(Game* g);
	virtual ~GameState();

	virtual bool handleEvent(const SDL_Event& e);
	virtual void update();
	virtual void render();

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
};