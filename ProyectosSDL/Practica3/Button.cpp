#include "Button.h"
#include "Game.h"

Button::Button() : currentState_(MOUSE_OUT), game_(nullptr), callback_(nullptr)
{
}

Button::Button(Texture * t, Vector2D p, double w, double h, CallbackOnClick cb, Game* g) :
	ArkanoidObject(t, p, w, h), currentState_(MOUSE_OUT), game_(g), callback_(cb)
{
}

Button::~Button()
{
}

bool Button::handleEvent(const SDL_Event & event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN &&
		event.button.button == SDL_BUTTON_LEFT)
	{
		SDL_Point mouse;
		SDL_GetMouseState(&mouse.x, &mouse.y);
		if (SDL_PointInRect(&mouse, &getRect()))
		{
			currentState_ = MOUSE_CLICK;
			callback_(game_);
			return true;
		}
		return false;
	}
	return false;
}

void Button::update()
{
	SDL_Point mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (SDL_PointInRect(&mouse, &getRect()))
		currentState_ = MOUSE_OVER;
	else
		currentState_ = MOUSE_OUT;
}

void Button::render()
{
	texture_->renderFrame(getRect(), 0, currentState_);
}