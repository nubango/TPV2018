#pragma once
#include "ArkanoidObject.h"

class MenuButton :
	public ArkanoidObject
{
public:
	MenuButton();
	MenuButton(Vector2D pos, uint width, uint height, Texture * texture);
	virtual ~MenuButton();
};