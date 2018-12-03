#pragma once
#include "HUD.h"

class Logo :
	public HUD
{
public:
	Logo();
	Logo(Vector2D pos, uint width, uint height, Texture* texture);
	virtual ~Logo();
};