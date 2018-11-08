#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Wall.h"
#include "HUD.h"

typedef unsigned int uint;

const uint WIN_WIDTH_PLUS_HUD = 1000;
const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 7;
const uint FRAME_RATE = 10;
const uint WALL_WIDTH = 20;
const uint PADDLE_WIDTH = 100;
const uint PADDLE_HEIGHT = 15;
const uint BALL_SIZE = 10;
const uint LOGO_HEIGHT = 60;
const string IMAGE_PATH = "..\\sprites\\";
const string LEVEL_PATH = "..\\levels\\level0";
const string LEVEL_EXTENSION = ".ark";

// Indices para el array de texturas
enum TextureName { BallTex, BricksTex, PaddleTex, SideWallTex, TopWallTex, LogoTex, NumbersTex };

// Struct con los atributos de la textura: path, filas y columnas
struct TextureAttributes {
	std::string filename;
	uint rows;
	uint cols;
};

class Game
{
private:
	// Array del struct de texturas (path, filas y columnas)
	const TextureAttributes textureAttributes_[NUM_TEXTURES] = {
	{"ball.png",1,1},
	{"bricks.png",2,3},
	{"paddle.png",1,1},
	{"side.png",1,1},
	{"topside.png",1,1},
	{"logo.png",1,1},
	{"numbers.png",1,10}
	};

	// Punteros de SDL
	SDL_Window* window_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;

	// Punteros a los objetos del juego
	Ball* ball_ = nullptr;
	BlocksMap* blocksmap_ = nullptr;
	Paddle* paddle_ = nullptr;
	Wall* sidewallleft_ = nullptr;
	Wall* sidewallright_ = nullptr;
	Wall* topwall_ = nullptr;
	HUD* hud_ = nullptr;

	// Booleanos de control de juego
	bool exit_ = false,
		win_ = false,
		gameover_ = false;

	// Variable para el numero de nivel
	int numLevel_ = 1;

	//variable para la cantidad de vidas
	int numLives_ = 3;

	// Array de punteros a las texturas del juego
	Texture* textures_[NUM_TEXTURES];

public:
	Game();
	~Game();

	Texture* getTexture(uint numTex) { return textures_[numTex]; }
	int getLives() { return numLives_; }

	// Contiene el bucle principal del juego
	void run();
	// Dibuja el estado actual del juego
	void render();
	// Actualiza el estado del juego
	void update();
	// Maneja eventos de teclado y raton
	void handleEvents();
	// Determina si la pelota colisiona con algun objeto y devuelve el vector de colision	
	bool collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector);
};