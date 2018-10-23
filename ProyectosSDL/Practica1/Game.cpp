#include "Game.h"

Game::Game()
{
	// Se inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Ejercicio 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";

	// Se crean las texturas
	for (uint i = 0; i < NUM_TEXTURES; i++)
	{
		textures_[i] = new Texture(renderer_);
		textures_[i]->load(IMAGE_PATH + textureAttributes_[i].filename, textureAttributes_[i].rows, textureAttributes_[i].cols);
	}

	// Se crean los objetos de la escena
	ball_ = new Ball({ WIN_WIDTH / 2 - 5,WIN_HEIGHT - 100 }, BALL_SIZE, BALL_SIZE, textures_[BallTex], this);
	paddle_ = new Paddle({ WIN_WIDTH / 2 - PADDLE_WIDTH/2,WIN_HEIGHT - 20 }, PADDLE_WIDTH, 10, textures_[PaddleTex]);
	sidewallleft_ = new Wall({ 0,0 }, WALL_WIDTH, WIN_HEIGHT, textures_[SideWallTex]);
	sidewallright_ = new Wall({ WIN_WIDTH - WALL_WIDTH,0 }, WALL_WIDTH, WIN_HEIGHT, textures_[SideWallTex]);
	topwall_ = new Wall({ 0,0 }, WIN_WIDTH, WALL_WIDTH, textures_[TopWallTex]);
	blocksmap_ = new BlocksMap(WIN_HEIGHT/2, WIN_WIDTH, this);
	blocksmap_->load(LEVEL_PATH + to_string(3) + LEVEL_EXTENSION); // ..\\levels\\level01.ark
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
	ball_->render();
	paddle_->render();
	blocksmap_->render();
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

bool Game::collides(Vector2D & collider)
{
	return false;
}
