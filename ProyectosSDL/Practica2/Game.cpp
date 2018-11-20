#include "Game.h"

Game::Game() : window_(nullptr), renderer_(nullptr), exit_(false), numLevel_(1)
{
	// Se inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("ARKANOID 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIN_WIDTH_PLUS_HUD, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
	if (window_ == nullptr || renderer_ == nullptr) throw "Error loading the SDL window or renderer";

	// Se crean las texturas
	for (uint i = 0; i < NUM_TEXTURES; i++)
	{
		textures_[i] = new Texture(renderer_);
		textures_[i]->load(IMAGE_PATH + textureAttributes_[i].filename, textureAttributes_[i].rows, textureAttributes_[i].cols);
	}

	// Se crean los objetos de la escena
	objects_.push_back(new Wall({ 0,0 }, WALL_SIZE, WIN_HEIGHT, { 1,0 }, textures_[SideWallTex]));
	objects_.push_back(new Wall({ WIN_WIDTH - WALL_SIZE,0 }, WALL_SIZE, WIN_HEIGHT, { -1,0 }, textures_[SideWallTex]));
	objects_.push_back(new Wall({ 0,0 }, WIN_WIDTH, WALL_SIZE, { 0,1 }, textures_[TopWallTex]));
	objects_.push_back(new Paddle({ WIN_WIDTH / 2 - PADDLE_WIDTH / 2,WIN_HEIGHT - 20 }, { 0,0 }, 7, PADDLE_WIDTH, PADDLE_HEIGHT, textures_[PaddleTex]));
	objects_.push_back(new Ball({ WIN_WIDTH / 2,WIN_HEIGHT - 20 - PADDLE_HEIGHT }, { 0,0 }, 5, BALL_SIZE, BALL_SIZE, textures_[BallTex], this));
	objects_.push_back(new BlocksMap({ double(WALL_SIZE),double(WALL_SIZE) }, WIN_WIDTH - (WALL_SIZE * 2), WIN_HEIGHT / 2, textures_[BricksTex]));
	objects_.back()->loadFromFile(LEVEL_PATH + to_string(numLevel_) + LEVEL_EXTENSION); // ..\\levels\\level01.ark
}

Game::~Game()
{
	// Destruye las texturas del array
	for (uint i = 0; i < NUM_TEXTURES; i++)
		delete textures_[i];

	// Destruye los objetos de la lista
	for (ArkanoidObject* o : objects_)
	{
		objects_.pop_back();
		delete o;
	}

	// Destruye variables de SDL
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

void Game::render() const
{
	SDL_RenderClear(renderer_);

	for (ArkanoidObject* o : objects_)
		o->render();

	SDL_RenderPresent(renderer_);
}

void Game::update()
{
	for (ArkanoidObject* o : objects_)
		o->update();
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) && !exit_)
	{
		if (event.type == SDL_QUIT)
			exit_ = true;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit_ = true;
		}

		for (ArkanoidObject* o : objects_)
			o->handleEvent(event);
	}
}

bool Game::collides(const SDL_Rect & rect, const Vector2D & vel, Vector2D & collVector)
{
	return false;
}
