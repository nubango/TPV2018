#include "MenuState.h"
#include "Game.h"

MenuState::MenuState()
{
}

MenuState::MenuState(Game * game) : GameState(game)
{
}

MenuState::~MenuState()
{
}

bool MenuState::handleEvent(const SDL_Event & e)
{
	if (GameState::handleEvent(e)) return true;
	return false;
}

void MenuState::update()
{
	GameState::update();
}

void MenuState::render()
{
	GameState::render();
}

bool MenuState::onEnter()
{
	SDL_Log("Entering Menu State...");
	stage_.push_back(new Button(game_->getTexture("PlayButton"),
		Vector2D(285, 275), 200, 50, Game::toPlayState, game_));
	stage_.push_back(new Button(game_->getTexture("ExitButton"),
		Vector2D(515, 275), 200, 50, Game::exit, game_));
	return true;
}

bool MenuState::onExit()
{
	SDL_Log("Exiting Menu State...");
	return true;
}