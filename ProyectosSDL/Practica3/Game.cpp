#include "Game.h"

const std::string Game::IMAGE_PATH = "..\\sprites\\";
const std::string Game::LEVEL_PATH = "..\\levels\\level0";
const std::string Game::FONT_PATH = "..\\fonts\\";
const std::string Game::CONFIG_PATH = "..\\config\\";
const std::string Game::FILE_EXTENSION = ".ark";
bool Game::exit_ = false;
GameStateMachine* Game::gsm_ = nullptr;

Game::Game() : SDLApp(WIN_WIDTH + UI_WIDTH, WIN_HEIGHT)
{
	initResources();
	initGame();
}

Game::~Game()
{
	// Reverse order to constructor
	closeGame();
	closeResources();
}

void Game::run()
{
	// Main game loop
	while (!exit_)
	{
		uint startTime = SDL_GetTicks();

		handleEvent();
		update();
		render();

		uint frameTime = SDL_GetTicks() - startTime;

		if (frameTime < (1000 / FRAME_RATE))
			SDL_Delay((1000 / FRAME_RATE) - frameTime);
	}
}

void Game::handleEvent()
{
	// Poll events
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (gsm_->currentState()->handleEvent(event)) return;
		else
		{
			if (event.type == SDL_QUIT)
			{
				exit_ = true;
			}
		}
	}
}

void Game::update()
{
	gsm_->currentState()->update();
}

void Game::render()
{
	// Render the scene
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_RenderClear(renderer_);
	gsm_->currentState()->render();
	SDL_RenderPresent(renderer_);
}

void Game::initResources()
{
	std::ifstream file;
	file.open(CONFIG_PATH + "resources" + FILE_EXTENSION);

	uint numTextures;
	file >> numTextures;

	SDL_Log("Loading textures...");
	for (int i = 0; i < numTextures; i++)
	{
		std::string key, value;
		uint rows, cols;

		file >> key >> value >> rows >> cols;

		textures_[key] = new Texture(renderer_, IMAGE_PATH + value, rows, cols);
	}

	uint numFonts;
	file >> numFonts;

	SDL_Log("Loading fonts...");
	for (int i = 0; i < numFonts; i++)
	{
		std::string key, value;
		uint size;

		file >> key >> value >> size;

		fonts_[key] = new Font(FONT_PATH + value, size);
	}

	file.close();
	SDL_Log("Resources loaded!");
}

void Game::closeResources()
{
	SDL_Log("Cleanning textures...");
	for (auto t : textures_)
	{
		delete t.second;
		t.second = nullptr;
	}

	SDL_Log("Cleanning fonts...");
	for (auto f : fonts_)
	{
		delete f.second;
		f.second = nullptr;
	}
	SDL_Log("Resources cleaned!");
}

void Game::initGame()
{
	gsm_ = new GameStateMachine();
	gsm_->pushState(new MenuState(this));
}

void Game::closeGame()
{
	delete gsm_;
	gsm_ = nullptr;
}

void Game::toPlayState(Game * g)
{
	gsm_->changeState(new PlayState(g));
}

void Game::toPauseState(Game * g)
{
	gsm_->pushState(new PauseState(g));
}

void Game::resumePlayState(Game * g)
{
	gsm_->popState();
}

void Game::toEndState(Game * g)
{
	gsm_->changeState(new EndState(g));
}

void Game::toMenuState(Game * g)
{
	gsm_->changeState(new MenuState(g));
}

void Game::exit(Game* g)
{
	exit_ = true;
}