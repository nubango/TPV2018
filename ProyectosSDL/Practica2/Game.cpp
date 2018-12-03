#include "Game.h"

const std::string Game::IMAGE_PATH = "..\\sprites\\";
const std::string Game::LEVEL_PATH = "..\\levels\\level0";
const std::string Game::LEVEL_EXTENSION = ".ark";

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
	Wall* leftSideWall = new Wall({ 0,0 }, WALL_SIZE, WIN_HEIGHT, { 1,0 }, textures_[SideWallTex]);
	Wall* rightSideWall = new Wall({ WIN_WIDTH - WALL_SIZE,0 }, WALL_SIZE, WIN_HEIGHT, { -1,0 }, textures_[SideWallTex]);
	Wall* topWall = new Wall({ 0,0 }, WIN_WIDTH, WALL_SIZE, { 0,1 }, textures_[TopWallTex]);
	Paddle * paddle = new Paddle({ WIN_WIDTH / 2 - PADDLE_WIDTH / 2,WIN_HEIGHT - 20 }, { 0,0 }, 7, PADDLE_WIDTH, PADDLE_HEIGHT, textures_[PaddleTex]);

	objects_.push_back(leftSideWall);
	objects_.push_back(rightSideWall);
	objects_.push_back(topWall);
	objects_.push_back(paddle);

	objects_.push_back(new Ball({ WIN_WIDTH / 2,WIN_HEIGHT - 20 - PADDLE_HEIGHT }, { 0,0 }, 5, BALL_SIZE, BALL_SIZE, textures_[BallTex], this));
	objects_.push_back(new BlocksMap({ double(WALL_SIZE),double(WALL_SIZE) }, WIN_WIDTH - (WALL_SIZE * 2), WIN_HEIGHT / 2, textures_[BricksTex]));
	// objects_.back()->loadFromFile(LEVEL_PATH + to_string(numLevel_) + LEVEL_EXTENSION); // ..\\levels\\level01.ark

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

	//for (auto it = objects_.begin(); it != objects_.end(); ++it)
	//{
	//	// (*(it++)->update());
	//	auto next = it;
	//	++next;
	//	(*it)->update();
	//	it = next;
	//}
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
	//// Si la componente Y de la bola esta en el espacio del mapa de bloques
	//if (ball_->getPos().getY() < blocksmap_->getBottomLimit() + 50)
	//{
	//	Block* block = blocksmap_->collides(ball_->getDestRect(), vel, collVector);
	//	if (block != nullptr)
	//	{
	//		blocksmap_->hitBlock(block); // Elimina el bloque con el que colisiona la bola
	//		if (blocksmap_->getNumBlocks() == 0)
	//			win_ = true;
	//		return true;
	//	}
	//}

	// Block* block = objects_.back()->collidesMap(rect, vel, collVector);

	// Muros y Paddle
	for (ArkanoidObject* o : collisionable_)
	{
		if (o->collides(rect, vel, collVector))
			return true;
		else
			return false;
	}
}

void Game::loadGame(string const& filename)
{
	ifstream file;
	file.open(filename);

	if (!file.is_open())
		throw ("Error: no se encuentra el fichero " + filename);
	else
	{
		for (ArkanoidObject* o : objects_)
			o->loadFromFile(file);
	}

	file.close();
}

void Game::saveGame(ofstream& file)
{
	// Version cutre: leer desde consola
	// Version buena: leer desde SDL (capturar numeros con decenas, centenas, etc...)
	// int code = readCode();
	// Crear fichero con ese nombre
	// ofstream file;
	// Se escribe en el fichero:
	// Se llama a saveToFile() de cada objeto
	//for (auto o : objects_)
	//	o->saveToFile(file);
	// El ejercicio es que la escena se guarde exactamente igual, no como en un juego
	// El bucle for va a dar fallos porque hay que saber donde acaban los objetos y donde comienzan los premios
	// Por ejemplo, con un atributo para saber cual es el firstReward (un entero)
	// for (int i = 0; i < firstReward; i++)
	//	objects_[i]->saveToFile();
	// Es mas facil con una class RewardsManager (paralelismo a BlocksMap) pero no es el "ejercicio"
	// file.close();
}

void Game::killObject(list<ArkanoidObject>::iterator it)
{
	//if (it == firstReward_)
	//	firstReward_++;
	//delete *it; // borra el propio reward
	//// eliminar de la lista el elemento
	//objects_.erase(it);
}