#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Wall.h"

typedef unsigned int uint;

const uint WIN_WIDTH = 800;
const uint WIN_HEIGHT = 600;
const uint NUM_TEXTURES = 5;
const uint FRAME_RATE = 60;

// Indices para el array de texturas
enum TextureName { BallTex, BricksTex, PaddleTex, SideWallTex, TopWallTex };

typedef struct TextureFile {
	std::string filename;
	uint rows;
	uint cols;
};

class Game
{
private:
	TextureFile texturefiles[NUM_TEXTURES] = {
	{"..\\images\\ball.png",1,1},
	{"..\\images\\bricks.png",2,3},
	{"..\\images\\paddle.png",1,1},
	{"..\\images\\side.png",1,1},
	{"..\\images\\topside.png",1,1}
	};

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
	bool exit_ = false;
	// gameover_,
	// win_;

	// Array de punteros a las texturas del juego
	Texture* textures_[NUM_TEXTURES];

public:
	Game();
	~Game();

	// Contiene el bucle principal del juego
	void run();
	// Dibuja el estado actual del juego
	void render();
	// Actualiza el estado del juego
	void update();
	// Maneja eventos de teclado y raton
	void handleEvents();
	// Determina si la pelota colisiona con algun objeto y devuelve el vector de colision	
	Vector2D collides();
};