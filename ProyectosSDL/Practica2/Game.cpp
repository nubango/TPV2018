#include "Game.h"

const std::string Game::IMAGE_PATH = "..\\sprites\\";
const std::string Game::LEVEL_PATH = "..\\levels\\level0";
const std::string Game::LEVEL_EXTENSION = ".ark";

Game::Game() :
	window_(nullptr), renderer_(nullptr), exit_(false), loaded_(false), win_(false), menu_(true), numLevel_(1), numLives_(3), code_(0)
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

	// Se crean los objetos del menu
	MenuButton* newButton = new MenuButton({ WIN_WIDTH / 4, WIN_HEIGHT / 2 }, 100, 50, textures_[NewGameTex]);
	MenuButton* loadButton = new MenuButton({ WIN_WIDTH / 4 * 3, WIN_HEIGHT / 2 }, 100, 50, textures_[LoadGameTex]);

	// Se agregan los objetos a la lista de menu
	menuObjects_.push_back(newButton);
	menuObjects_.push_back(loadButton);

	// Se crean los objetos de la escena
	Wall* leftSideWall = new Wall({ 0,0 }, WALL_SIZE, WIN_HEIGHT, { 1,0 }, textures_[SideWallTex]);
	Wall* rightSideWall = new Wall({ WIN_WIDTH - WALL_SIZE,0 }, WALL_SIZE, WIN_HEIGHT, { -1,0 }, textures_[SideWallTex]);
	Wall* topWall = new Wall({ 0,0 }, WIN_WIDTH, WALL_SIZE, { 0,1 }, textures_[TopWallTex]);
	Paddle * paddle = new Paddle({ WIN_WIDTH / 2 - PADDLE_WIDTH / 2,WIN_HEIGHT - 20 }, { 0,0 }, 7, PADDLE_WIDTH, PADDLE_HEIGHT, textures_[PaddleTex]);
	Ball * ball = new Ball({ WIN_WIDTH / 2,WIN_HEIGHT - 20 - PADDLE_HEIGHT }, { 0,0 }, 5, BALL_SIZE, BALL_SIZE, textures_[BallTex], this);
	BlocksMap * blocksMap = new BlocksMap({ double(WALL_SIZE),double(WALL_SIZE) }, WIN_WIDTH - (WALL_SIZE * 2), (WIN_HEIGHT / 2) - WALL_SIZE, textures_[BricksTex]);

	// Se agregan los objetos a la lista de objetos de juego
	objects_.push_back(leftSideWall);
	objects_.push_back(rightSideWall);
	objects_.push_back(topWall);
	objects_.push_back(paddle);
	objects_.push_back(ball);
	objects_.push_back(blocksMap);

	// Se agregan los objetos a la lista de colisionables
	collisionable_.push_back(leftSideWall);
	collisionable_.push_back(rightSideWall);
	collisionable_.push_back(topWall);
	collisionable_.push_back(paddle);
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

	for (ArkanoidObject* o : menuObjects_)
	{
		menuObjects_.pop_back();
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

	if (menu_)
	{
		for (ArkanoidObject* o : menuObjects_)
			o->render();
	}
	else
	{
		for (ArkanoidObject* o : objects_)
			o->render();
	}

	SDL_RenderPresent(renderer_);
}

void Game::update()
{
	if (menu_)
	{
		for (ArkanoidObject* o : menuObjects_)
			o->update();
	}
	else
	{
		for (ArkanoidObject* o : objects_)
			o->update();
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
		}

		if (menu_)
		{
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);
				if (x < WIN_WIDTH / 2)
					loaded_ = false;
				else if (x > WIN_WIDTH / 2)
					loaded_ = true;
				menu_ = false;
			}
			menuLoaded();
		}
		else
		{
			for (ArkanoidObject* o : objects_)
				o->handleEvent(event);
		}
	}
}

void Game::menuLoaded()
{
	// Carga de archivo los datos necesarios
	if (loaded_)
		loadGame(std::to_string(code_) + LEVEL_EXTENSION);
	else
		loadGame(LEVEL_PATH + std::to_string(numLevel_) + LEVEL_EXTENSION); // ..\\levels\\level01.ark
}

bool Game::collides(const SDL_Rect & rect, const Vector2D & vel, Vector2D & collVector)
{
	BlocksMap* blocksMap = static_cast<BlocksMap*>(objects_.back());
	Block* block = blocksMap->collidesBlock(rect, vel, collVector);

	if (block != nullptr)
	{
		blocksMap->hitBlock(block); // Elimina el bloque con el que colisiona la bola
		if (blocksMap->getNumBlocks() == 0)
			win_ = true;
		return true;
	}

	// Muros y Paddle
	for (ArkanoidObject* o : collisionable_)
	{
		if (o->collides(rect, vel, collVector))
			return true;
	}
	return false;
}

void Game::loadGame(string const& filename)
{
	ifstream file;
	file.open(filename);

	if (!file.is_open())
		throw ("Error: no se encuentra el fichero " + filename);
	else
	{
		if (loaded_)
		{
			for (ArkanoidObject* o : objects_)
				o->loadFromFile(file);
		}
		else
			// Si no es un archivo de guardado solo necesitamos la informacion de blocksMap
			// que es el ultimo objeto de la lista
			static_cast<BlocksMap*>(objects_.back())->loadFromFile(file);
	}

	file.close();
}

void Game::saveGame()
{
	// Version cutre: leer desde consola
	// Version buena: leer desde SDL (capturar numeros con decenas, centenas, etc...)

	code_; // = readCode();
	// Crear fichero con ese nombre
	ofstream file;
	file.open(std::to_string(code_) + LEVEL_EXTENSION);

	file << numLevel_ << " " << numPoints_ << " " << numLives_;

	for (ArkanoidObject* o : objects_)
		o->saveToFile(file);

	// El ejercicio es que la escena se guarde exactamente igual, no como en un juego
	// El bucle for va a dar fallos porque hay que saber donde acaban los objetos y donde comienzan los premios
	// Por ejemplo, con un atributo para saber cual es el firstReward (un entero)
	// for (int i = 0; i < firstReward; i++)
	// objects_[i]->saveToFile();
	// Es mas facil con una class RewardsManager (paralelismo a BlocksMap) pero no es el "ejercicio"
	file.close();
}

void Game::killObject(list<ArkanoidObject>::iterator it)
{
	//if (it == firstReward_)
	//	firstReward_++;
	//delete *it; // borra el propio reward
	//// eliminar de la lista el elemento
	//objects_.erase(it);
}

bool Game::isCollidingPaddle(const SDL_Rect & rect)
{
	Paddle* paddle = nullptr;
	for (ArkanoidObject* o : objects_)
		paddle = static_cast<Paddle*>(o);

	return SDL_HasIntersection(&rect, &paddle->getRect());
}

void Game::nextLevel()
{
	numLevel_++;
	BlocksMap* blocksMap = static_cast<BlocksMap*>(objects_.back());
	ifstream file;
	file.open(LEVEL_PATH + std::to_string(numLevel_) + LEVEL_EXTENSION);
	blocksMap->loadFromFile(file);
}

void Game::addLive()
{
	numLives_++;
}

void Game::biggerPaddle()
{
	Paddle* paddle = nullptr;
	for (ArkanoidObject* o : objects_)
		paddle = static_cast<Paddle*>(o);

	paddle->setW(paddle->getW() * 1.5);
}

void Game::smallerPaddle()
{
	Paddle* paddle = nullptr;
	for (ArkanoidObject* o : objects_)
		paddle = static_cast<Paddle*>(o);

	paddle->setW(paddle->getW() * 0.75);
}