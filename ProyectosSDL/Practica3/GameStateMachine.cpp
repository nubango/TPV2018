#include "GameStateMachine.h"

GameStateMachine::GameStateMachine()
{
}

GameStateMachine::~GameStateMachine()
{
	while (!states_.empty())
		states_.pop();
}

GameState * GameStateMachine::currentState()
{
	if (!states_.empty())
		return states_.top();
	else
		return nullptr;
}

void GameStateMachine::popState()
{
	if (!states_.empty())
	{
		if (states_.top()->onExit())
		{
			GameState* s = states_.top();
			delete s; s = nullptr;
			states_.pop();
		}
	}
}

void GameStateMachine::pushState(GameState* state)
{
	states_.push(state);
	state->onEnter();
}

void GameStateMachine::changeState(GameState* state)
{
	popState();
	pushState(state);
}