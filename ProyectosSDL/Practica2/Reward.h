#pragma once
#include "MovingObject.h"

class Reward :
	public MovingObject
{
public:
	Reward();
	virtual ~Reward();

	void render();
	void update();
	void handleEvent(SDL_Event & event);

	virtual void loadFromFile();
	virtual void saveToFile();
};