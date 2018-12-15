#include "Reward.h"

Reward::Reward() : MovingObject()
{
}

Reward::Reward(Vector2D pos, Vector2D dir, double speed, double width, double height, Texture * texture, Game* game) :
	MovingObject(pos, dir, speed, width, height, texture), game_(game)
{
}

void Reward::render()
{
}

void Reward::update()
{
	MovingObject::update();
	if (game_->isOutOfWindow(pos_.getY())) // Si estoy en la posicion de abajo del todo (preguntar a game)
		if (game_->isCollidingPaddle(getRect())) // Si has chocado con la pala (preguntar a game)
			this->action();
	game_->killObject(itList_);
	// despues de esto no puede llamarse a nada del objeto, es arriesgado y seria memoria no valida, el objeto ya no existe
}

void Reward::loadFromFile(ifstream & file)
{
}

void Reward::saveToFile()
{
}

//----------------------------------------------------------------------------

RedReward::RedReward() : Reward()
{
}

void RedReward::action()
{
	game_->nextLevel();
}

//----------------------------------------------------------------------------

BlackReward::BlackReward() : Reward()
{
}

void BlackReward::action()
{
	game_->addLive();
}

//----------------------------------------------------------------------------

BlueReward::BlueReward() : Reward()
{
}

void BlueReward::action()
{
	game_->biggerPaddle();
}

//----------------------------------------------------------------------------

OrangeReward::OrangeReward() : Reward()
{
}

void OrangeReward::action()
{
	game_->smallerPaddle();
}