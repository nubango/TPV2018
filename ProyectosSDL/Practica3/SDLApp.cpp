#include "SDLApp.h"

const std::string SDLApp::WIN_TITLE = "ARKANOID 3.0";

SDLApp::SDLApp(uint w, uint h)
{
	SDL_Log("Initializing SDL...");

	// Init SDL Libraries
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	TTF_Init();

	// Init SDL Rendering Engine
	window_ = SDL_CreateWindow(WIN_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// Init random seed generator
	srand(static_cast<unsigned int>(time(NULL)));

	SDL_Log("SDL initialized successfully!");
}

SDLApp::~SDLApp()
{
	SDL_Log("Closing SDL...");

	// Free SDL Resources
	SDL_DestroyRenderer(renderer_); renderer_ = nullptr;
	SDL_DestroyWindow(window_); window_ = nullptr;

	// Close SDL Libraries
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	SDL_Log("SDL closed successfully!");
}