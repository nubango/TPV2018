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
	paddle_ = new Paddle({ WIN_WIDTH / 2 - PADDLE_WIDTH / 2,WIN_HEIGHT - 20 }, PADDLE_WIDTH, 10, textures_[PaddleTex]);
	sidewallleft_ = new Wall({ 0,0 }, WALL_WIDTH, WIN_HEIGHT, textures_[SideWallTex]);
	sidewallright_ = new Wall({ WIN_WIDTH - WALL_WIDTH,0 }, WALL_WIDTH, WIN_HEIGHT, textures_[SideWallTex]);
	topwall_ = new Wall({ 0,0 }, WIN_WIDTH, WALL_WIDTH, textures_[TopWallTex]);
	blocksmap_ = new BlocksMap(WIN_HEIGHT / 2, WIN_WIDTH, this);
	blocksmap_->load(LEVEL_PATH + to_string(numLevel_) + LEVEL_EXTENSION); // ..\\levels\\level01.ark
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
	SDL_RenderClear(renderer_);
	topwall_->render();
	sidewallleft_->render();
	sidewallright_->render();
	ball_->render();
	paddle_->render();
	blocksmap_->render();
	SDL_RenderPresent(renderer_);

	// DEBUG POR CONSOLA
	system("cls");
	cout << "Lives: " << lives_ << endl;
	cout << "Level " << numLevel_ << endl;
	cout << "Ball position: { " << ball_->getPos().getX() << " , " << ball_->getPos().getY() << " }" << endl;
	cout << "Ball direction: { " << ball_->getVel().getX() << " , " << ball_->getVel().getY() << " }" << endl;
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
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit_ = true;
		}
		paddle_->handleEvents(event);
	}
}

bool Game::collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector)
{
	// Si la componente Y de la bola esta en el espacio del mapa de bloques
	if (ball_->getPos().getY() > blocksmap_->getBottomLimit())
	{
		Block* block = blocksmap_->collides(ball_->getDestRect(), ball_->getVel(), collVector);
		if (block != nullptr)
		{
			blocksmap_->hitBlock(block); // Elimina el bloque con el que colisiona la bola
			if (blocksmap_->getNumBlocks() == 0)
				win_ = true;
		}
		return true;
	}

	// Muros
	// if (SDL_HasIntersection(&rect, &rect));
	if (topwall_->collides(collVector) || sidewallright_->collides(collVector) || sidewallleft_->collides(collVector))
		return true;

	// Paddle
	if (paddle_->collides(collVector))
		return true;
}