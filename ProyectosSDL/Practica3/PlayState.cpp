#include "PlayState.h"
#include "Game.h"

PlayState::PlayState()
{
}

PlayState::PlayState(Game * game) : GameState(game)
{
}

PlayState::~PlayState()
{
}

bool PlayState::handleEvent(const SDL_Event & e)
{
	if (GameState::handleEvent(e))
		return true;

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			Game::toEndState(game_);
			break;

		case SDLK_ESCAPE:
			Game::toPauseState(game_);
			break;
		}
		return true;
	}
	return false;
}

void PlayState::update()
{
	GameState::update();
}

void PlayState::render()
{
	GameState::render();
}

bool PlayState::onEnter()
{
	SDL_Log("Entering Play State...");

	// Create walls
	Wall* w;
	w = new Wall(game_->getTexture("SideWall"), Vector2D(0, Game::WALL_SIZE), Vector2D(1, 0), Game::WALL_SIZE, Game::WIN_HEIGHT);
	stage_.push_back(w);
	w = new Wall(game_->getTexture("SideWall"), Vector2D(Game::WIN_WIDTH - Game::WALL_SIZE, Game::WALL_SIZE), Vector2D(-1, 0), Game::WALL_SIZE, Game::WIN_HEIGHT);
	stage_.push_back(w);
	w = new Wall(game_->getTexture("TopWall"), Vector2D(-4, 0), Vector2D(0, 1), (double)(Game::WIN_WIDTH + 8), Game::WALL_SIZE);
	stage_.push_back(w);

	return true;
}

bool PlayState::onExit()
{
	SDL_Log("Exiting Play State...");
	return true;
}