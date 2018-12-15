#pragma once
#include "MovingObject.h"
#include "Game.h"
#include <list>

class Reward :
	public MovingObject
{
protected:
	Game* game_;
	list<ArkanoidObject>::iterator itList_;

public:
	Reward();
	Reward(Vector2D pos, Vector2D dir, double speed, double width, double height, Texture * texture, Game * game);
	virtual ~Reward() {};

	virtual void setIterator(const list<ArkanoidObject>::iterator &it){ itList_ = it; }

	virtual void render();
	virtual void update();
	
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
	virtual ~RedReward() {};

	virtual void action();
};

//----------------------------------------------------------------------------

class BlackReward :
	public Reward
{
public:
	BlackReward();
	virtual ~BlackReward() {};

	virtual void action();
};

//----------------------------------------------------------------------------

class BlueReward :
	public Reward
{
public:
	BlueReward();
	virtual ~BlueReward() {};

	virtual void action();
};

//----------------------------------------------------------------------------

class OrangeReward :
	public Reward
{
public:
	OrangeReward();
	virtual ~OrangeReward() {};

	virtual void action();
};