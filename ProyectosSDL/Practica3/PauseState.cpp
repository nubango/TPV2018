#include "PauseState.h"
#include "Game.h"

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

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			Game::resumePlayState(game_);
			break;
		}
		return true;
	}

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
	SDL_Log("Entering Pause State...");
	stage_.push_back(new Button(game_->getTexture("ResumeButton"),
		Vector2D(400, 275), 200, 50, Game::resumePlayState, game_));
	return true;
}

bool PauseState::onExit()
{
	SDL_Log("Exiting Pause State...");
	return true;
}