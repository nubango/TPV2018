#pragma once
#include "Vector2D.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Wall.h"

typedef unsigned int uint;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 5;
const uint FRAME_RATE = 60;
const uint WALL_WIDTH = 20;
const uint PADDLE_WIDTH = 100;
const uint BALL_SIZE = 10;
const string IMAGE_PATH = "..\\sprites\\";
const string LEVEL_PATH = "..\\levels\\level0";
const string LEVEL_EXTENSION = ".ark";
/// Velocidades, tamanos

// Indices para el array de texturas
enum TextureName { BallTex, BricksTex, PaddleTex, SideWallTex, TopWallTex };

// Struct con los atributos de la textura: path, filas y columnas
typedef struct TextureAttributes {
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
	{"topside.png",1,1}
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

	// Booleanos de control de juego
	bool exit_ = false,
		gameover_ = false,
		win_ = false;

	// Variable para el numero de nivel
	int numLevel = 1;

	// Array de punteros a las texturas del juego
	Texture* textures_[NUM_TEXTURES];

public:
	Game();
	~Game();

	Texture* getTexture(uint numTex) { return textures_[numTex]; }

	// Contiene el bucle principal del juego
	void run();
	// Dibuja el estado actual del juego
	void render();
	// Actualiza el estado del juego
	void update();
	// Maneja eventos de teclado y raton
	void handleEvents();
	// Determina si la pelota colisiona con algun objeto y devuelve el vector de colision	
	bool collides(Vector2D& collider);
};