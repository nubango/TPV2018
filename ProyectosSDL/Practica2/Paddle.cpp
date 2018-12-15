#include "Paddle.h"
#include "Game.h"

Paddle::Paddle() :
	MovingObject()
{
}

Paddle::Paddle(Vector2D pos, Vector2D dir, double speed, double width, double height, Texture * texture) :
	MovingObject(pos, dir, speed, width, height, texture)
{
}

Paddle::~Paddle()
{
}

void Paddle::update()
{
	MovingObject::update();
	// Si la posicion no es valida lo devuelve a una posicion que si lo es
	if (pos_.getX() <= Game::WALL_SIZE)
		pos_.setX(Game::WALL_SIZE);
	else if (pos_.getX() >= Game::WIN_WIDTH - Game::WALL_SIZE - width_)
		pos_.setX(Game::WIN_WIDTH - Game::WALL_SIZE - width_);
}

void Paddle::handleEvent(SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_RIGHT)
			dir_.setX(1);
		if (event.key.keysym.sym == SDLK_LEFT)
			dir_.setX(-1);
	}
	if (event.type == SDL_KEYUP)
		dir_.setX(0);
}

bool Paddle::collides(const SDL_Rect & rect, const Vector2D & vel, Vector2D & collVector)
{
	// SDL_HasIntersection comprueba si hay colision entre dos SDL_Rects
	// DestRect es la propia pala
	if (ArkanoidObject::collides(rect, vel, collVector))
	{
		//double coefX = ((rect.x - pos_.getX()) / (width_ - rect.w))
		//	- (1 - (rect.x - pos_.getX()) / (width_ - rect.w));
		//double coefY = (rect.x - pos_.getX()) / (width_ - rect.w);

		//collVector = Vector2D(coefX, -coefY);
		//return true;

		//--------------------------------------------------------------------------------

		double midPoint = getRect().x + getRect().w / 2;
		// Si colisiona por el lado izquierdo
		if (rect.x < midPoint)
		{
			// Si viene del lado opuesto
			if (vel.getX() == -1)
				collVector = Vector2D(0, -1);
			// Si viene del mismo lado
			else
				collVector = Vector2D(-1, -1);
		}
		// Si colisiona por el lado derecho
		else
		{
			// Si viene del lado opuesto
			if (vel.getX() == -1)
				collVector = Vector2D(-1, -1);
			// Si viene del mismo lado
			else
				collVector = Vector2D(0, -1);
		}
		return true;

		//--------------------------------------------------------------------------------

		// collVector = Vector2D(0, -1);
		// return true;
	}
	return false;
}