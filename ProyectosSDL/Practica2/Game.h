#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"
#include "ArkanoidError.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "BlocksMap.h"
#include <list>

typedef unsigned int uint;

const uint WIN_WIDTH = 800;
const uint WIN_WIDTH_PLUS_HUD = WIN_WIDTH + 200;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 7;
const uint FRAME_RATE = 30; // A menor tiempo de espera entre frames, mayor la velocidad del bucle

const uint WALL_SIZE = 20;
const uint BALL_SIZE = 10;
const uint PADDLE_WIDTH = 100;
const uint PADDLE_HEIGHT = 15;

const string IMAGE_PATH = "..\\sprites\\";
const string LEVEL_PATH = "..\\levels\\level0";
const string LEVEL_EXTENSION = ".ark";

// Indices para el array de texturas
enum TextureName { BallTex, BricksTex, PaddleTex, SideWallTex, TopWallTex, LogoTex, NumbersTex };

// Struct con los atributos de la textura: path, filas y columnas
struct TextureAttributes 
{
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

	// Array de punteros a las texturas del juego
	Texture* textures_[NUM_TEXTURES];

	// Punteros de SDL
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	// Objetos del juego (polimorfismo)
	list <ArkanoidObject*> objects_;

	// Booleanos de control de juego
	bool exit_;

	// Variables del juego
	int numLevel_;

public:
	Game();
	~Game();

	Texture* getTexture(uint numTex) { return textures_[numTex]; }

	void run();
	void render() const;
	void update();
	void handleEvents();

	// Determina si la pelota colisiona con algun objeto y devuelve el vector de colision	
	bool collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector);
};