#pragma once
#include "ArkanoidObject.h"

class Game;
using CallbackOnClick = void(Game* g);

class Button :
	public ArkanoidObject
{
	enum state { MOUSE_OUT, MOUSE_OVER, MOUSE_CLICK };

private:
	Game* game_;
	state currentState_;
	CallbackOnClick* callback_;

public:
	Button();
	Button(Texture* t, Vector2D p, double w, double h, CallbackOnClick cb, Game* g);
	virtual ~Button();

	virtual bool handleEvent(const SDL_Event& event);
	virtual void update();
	virtual void render();
};