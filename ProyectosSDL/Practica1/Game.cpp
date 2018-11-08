#include "Game.h"

Game::Game()
{
	// Se inicializa SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	window_ = SDL_CreateWindow("Ejercicio 3", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
	ball_ = new Ball({ WIN_WIDTH / 2,WIN_HEIGHT - 30 }, BALL_SIZE, BALL_SIZE, textures_[BallTex], this);
	paddle_ = new Paddle({ WIN_WIDTH / 2 - PADDLE_WIDTH / 2,WIN_HEIGHT - 20 }, PADDLE_WIDTH, PADDLE_HEIGHT, textures_[PaddleTex]);
	sidewallleft_ = new Wall({ 0,0 }, WALL_WIDTH, WIN_HEIGHT, { 1,0 }, textures_[SideWallTex]);
	sidewallright_ = new Wall({ WIN_WIDTH - WALL_WIDTH,0 }, WALL_WIDTH, WIN_HEIGHT, { -1,0 }, textures_[SideWallTex]);
	topwall_ = new Wall({ 0,0 }, WIN_WIDTH, WALL_WIDTH, { 0,1 }, textures_[TopWallTex]);
	blocksmap_ = new BlocksMap(WIN_HEIGHT / 2, WIN_WIDTH, this);
	blocksmap_->load(LEVEL_PATH + to_string(numLevel_) + LEVEL_EXTENSION); // ..\\levels\\level01.ark
	hud_ = new HUD({ WIN_WIDTH_PLUS_HUD - (WIN_WIDTH_PLUS_HUD - WIN_WIDTH), 0 }, WIN_WIDTH_PLUS_HUD - WIN_WIDTH, WIN_HEIGHT, textures_[PaddleTex], textures_[LogoTex], textures_[NumbersTex], this);
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
	delete hud_;
	ball_ = nullptr;
	paddle_ = nullptr;
	sidewallleft_ = nullptr;
	sidewallright_ = nullptr;
	topwall_ = nullptr;
	blocksmap_ = nullptr;
	hud_ = nullptr;
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::run()
{
	while (!exit_ && !win_ && !gameover_)
	{
		while (!win_ && !gameover_)
		{
			uint startTime = SDL_GetTicks();
			handleEvents();
			update();
			render();
			uint frameTime = SDL_GetTicks() - startTime;
			if (frameTime < FRAME_RATE) SDL_Delay(FRAME_RATE - frameTime);
		}

		if (win_)
		{
			// Si ganas te carga el siguiente nivel
			cout << "YOU WIN LEVEL " << numLevel_ << endl;
			numLevel_++;
			blocksmap_->load(LEVEL_PATH + to_string(numLevel_) + LEVEL_EXTENSION);
			ball_->reset();
			win_ = false;
		}
		else if (gameover_)
		{
			exit_ = true;
			cout << "YOU LOSE ALL YOUR LIVES";
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer_);
	topwall_->render();
	sidewallleft_->render();
	sidewallright_->render();
	paddle_->render();
	blocksmap_->render();
	ball_->render();
	hud_->render();
	SDL_RenderPresent(renderer_);
}

void Game::update()
{
	paddle_->update();
	if (!ball_->isOutOfBounds())
		ball_->update();
	else
	{
		if (numLives_ > 0)
			numLives_--;
		if(numLives_ == 0)
			gameover_ = true;
		ball_->reset();
	}
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

			// ------------- DEBUG --------------- //
			if (event.key.keysym.sym == SDLK_1)
				win_ = true;
			if (event.key.keysym.sym == SDLK_2)
				gameover_ = true;
			if (event.key.keysym.sym == SDLK_3)
				numLives_--;
		}
		paddle_->handleEvents(event);
	}
}

bool Game::collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector)
{
	// Si la componente Y de la bola esta en el espacio del mapa de bloques
	if (ball_->getPos().getY() < blocksmap_->getBottomLimit() + 50)
	{
		Block* block = blocksmap_->collides(ball_->getDestRect(), vel, collVector);
		if (block != nullptr)
		{
			blocksmap_->hitBlock(block); // Elimina el bloque con el que colisiona la bola
			if (blocksmap_->getNumBlocks() == 0)
				win_ = true;
			return true;
		}
	}

	// Muros
	if (topwall_->collides(rect, vel, collVector))
		return true;
	if (sidewallright_->collides(rect, vel, collVector))
		return true;
	if (sidewallleft_->collides(rect, vel, collVector))
		return true;

	// Paddle
	if (paddle_->collides(rect, vel, collVector))
		return true;

	return false;
}