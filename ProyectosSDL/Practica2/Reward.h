#pragma once
#include "MovingObject.h"
#include "Game.h"
#include <list>

class Reward :
	public MovingObject
{
private:
	Game* game_;
	list<ArkanoidObject>::iterator itList;

public:
	Reward();
	virtual ~Reward();

	virtual void render();
	virtual void update();
	virtual void handleEvent(SDL_Event & event);
	
	virtual void action() = 0;

	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile();
};

//----------------------------------------------------------------------------

class RedReward :
	public Reward
{
public:
	RedReward();
	virtual ~RedReward();

	virtual void action();
};

//----------------------------------------------------------------------------

class BlackReward :
	public Reward
{
public:
	BlackReward();
	virtual ~BlackReward();

	virtual void action();
};

//----------------------------------------------------------------------------

class BlueReward :
	public Reward
{
public:
	BlueReward();
	virtual ~BlueReward();

	virtual void action();
};

//----------------------------------------------------------------------------

class OrangeReward :
	public Reward
{
public:
	OrangeReward();
	virtual ~OrangeReward();

	virtual void action();
};