#include "Game.h"

Game::Game()
{
	// We first initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Ejercicio 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";

	// We now create the textures
	for (uint i = 0; i < NUM_TEXTURES; i++)
	{
		textures_[i] = new Texture(renderer_);
		textures_[i]->load(texturefiles[i].filename, texturefiles[i].rows, texturefiles[i].cols);
	}

	// We finally create the game objects
	ball_ = new Ball({ WIN_WIDTH / 2 - 5,WIN_HEIGHT - 100 }, 10, 10, textures_[BallTex], this);
	paddle_ = new Paddle({ WIN_WIDTH / 2 - 50,WIN_HEIGHT - 20 }, 100, 10, textures_[PaddleTex]);
	sidewallleft_ = new Wall({ 0,0 }, 20, WIN_HEIGHT, textures_[SideWallTex]);
	sidewallright_ = new Wall({ WIN_WIDTH - 20,0 }, 20, WIN_HEIGHT, textures_[SideWallTex]);
	topwall_ = new Wall({ 0,0 }, WIN_WIDTH, 20, textures_[TopWallTex]);
	blocksmap_ = new BlocksMap();
}

Game::~Game()
{
	for (uint i = 0; i < NUM_TEXTURES; i++)
		delete textures_[i];
	delete ball_;
	delete paddle_;
	delete sidewallleft_;
	delete sidewallright_;
	delete topwall_;
	delete blocksmap_;
	ball_ = nullptr;
	paddle_ = nullptr;
	sidewallleft_ = nullptr;
	sidewallright_ = nullptr;
	topwall_ = nullptr;
	blocksmap_ = nullptr;
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::run()
{
	while (!exit_)
	{
		uint startTime = SDL_GetTicks();
		handleEvents();
		update();
		render();
		uint frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
	}
}

void Game::render()
{
	topwall_->render();
	sidewallleft_->render();
	sidewallright_->render();
	blocksmap_->render();
	ball_->render();
	paddle_->render();
	SDL_RenderPresent(renderer_);
}

void Game::update()
{
	ball_->update();
	paddle_->update();
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit_)
	{
		if (event.type == SDL_QUIT)
			exit_ = true;
		paddle_->handleEvents(event);
	}
}

Vector2D Game::collides()
{
	return Vector2D();
}