#include "PauseState.h"

PauseState::PauseState()
{
}

PauseState::PauseState(Game * game) : GameState(game)
{
}

PauseState::~PauseState()
{
}

bool PauseState::handleEvent(const SDL_Event & e)
{
	if (GameState::handleEvent(e)) return true;
	return false;
}

void PauseState::update()
{
	GameState::update();
}

void PauseState::render()
{
	GameState::render();
}

bool PauseState::onEnter()
{
	return false;
}

bool PauseState::onExit()
{
	return false;
}