#include "Reward.h"

Reward::Reward() : MovingObject()
{
}

Reward::~Reward()
{
}

void Reward::render()
{
}

void Reward::update()
{
	//MovingObject::update();
	//if (...) // Si estoy en la posicion de abajo del todo (preguntar a game)
	//	if (...) // Si has chocado con la pala (preguntar a game)
	//		this->action(); // game_->funcionquehaccosas();
	//game_->killObject(itList);
	//// despues de esto no puede llamarse a nada del objeto, es arriesgado y seria memoria no valida
	//// el objeto ya no existiría
}

void Reward::handleEvent(SDL_Event & event)
{
}

void Reward::action()
{
}

void Reward::loadFromFile(ifstream & file)
{
}

void Reward::saveToFile()
{
}

//----------------------------------------------------------------------------

RedReward::RedReward()
{
}

RedReward::~RedReward()
{
}

void RedReward::action()
{
}

//----------------------------------------------------------------------------

BlackReward::BlackReward()
{
}

BlackReward::~BlackReward()
{
}

void BlackReward::action()
{
}

//----------------------------------------------------------------------------

BlueReward::BlueReward()
{
}

BlueReward::~BlueReward()
{
}

void BlueReward::action()
{
}

//----------------------------------------------------------------------------

OrangeReward::OrangeReward()
{
}

OrangeReward::~OrangeReward()
{
}

void OrangeReward::action()
{
}