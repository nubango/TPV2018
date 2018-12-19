#include "EndState.h"
#include "Game.h"

EndState::EndState()
{
}

EndState::EndState(Game * game) : GameState(game)
{
}

EndState::~EndState()
{
}

bool EndState::handleEvent(const SDL_Event & e)
{
	if (GameState::handleEvent(e)) return true;
	return false;
}

void EndState::update()
{
	GameState::update();
}

void EndState::render()
{
	GameState::render();
}

bool EndState::onEnter()
{
	SDL_Log("Entering End State...");
	stage_.push_back(new Button(game_->getTexture("MenuButton"),
		Vector2D(285, 275), 200, 50, Game::toMenuState, game_));
	stage_.push_back(new Button(game_->getTexture("ExitButton"),
		Vector2D(515, 275), 200, 50, Game::exit, game_));
	return true;
}

bool EndState::onExit()
{
	SDL_Log("Exiting Exit State...");
	return true;
}