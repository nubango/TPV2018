#pragma once

#include "SDLIncludes.h"

class SDLApp
{
public:
	static const uint WIN_WIDTH = 800;
	static const uint WIN_HEIGHT = 600;

	static const std::string WIN_TITLE;

protected:
	SDL_Window* window_;
	SDL_Renderer* renderer_;

public:
	// Constructora que toma como valores por defecto las constantes
	SDLApp(uint w = WIN_WIDTH, uint h = WIN_HEIGHT);
	virtual ~SDLApp();
};