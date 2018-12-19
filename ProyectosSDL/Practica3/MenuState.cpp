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

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			Game::toPlayState(game_);
			break;

		case SDLK_ESCAPE:
			Game::exit(game_);
			break;
		}
		return true;
	}

	return false;
}

void MenuState::update()
{
	GameState::update();
}

void MenuState::render()
{
	GameState::render();

	game_->getTexture("Logo")->render({ 250,50,500,200 });
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