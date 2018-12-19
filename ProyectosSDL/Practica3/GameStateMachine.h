#pragma once
#include "GameState.h"

class GameStateMachine
{
private:
	std::stack<GameState*> states_;

public:
	GameStateMachine();
	~GameStateMachine();

	GameState* currentState();
	void popState();
	void pushState(GameState* state);
	void changeState(GameState* state);
};