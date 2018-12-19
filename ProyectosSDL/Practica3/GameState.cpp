#include "Game.h"
#include "GameState.h"

GameState::GameState(): game_(nullptr)
{
}

GameState::GameState(Game * g) : game_(g)
{
}

GameState::~GameState()
{
	for (GameObject* o : stage_)
	{
		delete o;
		o = nullptr;
	}
}

bool GameState::handleEvent(const SDL_Event & e)
{
	bool handled = false;
	auto it = stage_.begin();
	while (!handled && it != stage_.end())
	{
		if ((*it)->handleEvent(e)) handled = true;
		else it++;
	}
	return handled;
}

void GameState::update()
{
	for (GameObject* o : stage_)
		o->update();
}

void GameState::render()
{
	for (GameObject* o : stage_)
		o->render();
}