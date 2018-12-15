#pragma once
#include "checkML.h"
#include "ArkanoidObject.h"
#include "ArkanoidError.h"
#include "Paddle.h"
#include "Ball.h"
#include "Wall.h"
#include "BlocksMap.h"
#include "MenuButton.h"
#include <list>
#include <SDL_ttf.h>

typedef unsigned int uint;

// Indices para el array de texturas
enum TextureName { BallTex, BricksTex, PaddleTex, SideWallTex, TopWallTex, LogoTex, NumbersTex, NewGameTex, LoadGameTex };

// Struct con los atributos de la textura: path, filas y columnas
struct TextureAttributes
{
	std::string filename;
	uint rows;
	uint cols;
};

class Game
{
public:
	static const uint WIN_WIDTH = 800;
	static const uint WIN_WIDTH_PLUS_HUD = WIN_WIDTH + 200;
	static const uint WIN_HEIGHT = 600;
	static const uint NUM_TEXTURES = 9;
	static const uint FRAME_RATE = 30; // A menor tiempo de espera entre frames, mayor la velocidad del bucle

	static const uint WALL_SIZE = 20;
	static const uint BALL_SIZE = 10;
	static const uint PADDLE_WIDTH = 100;
	static const uint PADDLE_HEIGHT = 15;
	static const uint LOGO_HEIGHT = 60;

	static const std::string IMAGE_PATH;
	static const std::string LEVEL_PATH;
	static const std::string LEVEL_EXTENSION;

private:
	// Array del struct de texturas (path, filas y columnas)
	const TextureAttributes textureAttributes_[NUM_TEXTURES] = {
	{"ball.png",1,1},
	{"bricks.png",2,3},
	{"paddle.png",1,1},
	{"side.png",1,1},
	{"topside.png",1,1},
	{"logo.png",1,1},
	{"numbers.png",1,10},
	{"newGameButton.png",1,1},
	{"loadGameButton.png",1,1}
	};

	// Array de punteros a las texturas del juego
	Texture* textures_[NUM_TEXTURES];

	// Punteros de SDL
	SDL_Window* window_;
	SDL_Renderer* renderer_;

	// Objetos del juego (polimorfismo)
	list <ArkanoidObject*> objects_;
	// Lista de objetos colisionables
	list <ArkanoidObject*> collisionable_;
	// Lista de objetos del menu
	list <ArkanoidObject*> menuObjects_;

	// Iterador al primer Reward
	list<ArkanoidObject>::iterator firstReward_;

	// Booleanos de control de juego
	bool exit_;
	bool loaded_;
	bool win_;
	bool menu_;

	// Variables del juego
	uint numLevel_;
	uint numLives_;
	uint numPoints_;

	uint code_;

public:
	Game();
	~Game();

	Texture* getTexture(uint numTex) { return textures_[numTex]; }
	uint getLives() { return numLives_; }

	void run();
	void render() const;
	void update();
	void handleEvents();

	void menuLoaded();

	// Determina si la pelota colisiona con algun objeto y devuelve el vector de colision	
	bool collides(const SDL_Rect& rect, const Vector2D & vel, Vector2D& collVector);
	void loadGame(string const& filename);
	void saveGame();

	void killObject(list<ArkanoidObject>::iterator it);
	bool isOutOfWindow(double posY) { return (posY > WIN_HEIGHT); }
	bool isCollidingPaddle(const SDL_Rect& rect);

	void nextLevel();
	void addLive();
	void biggerPaddle();
	void smallerPaddle();
};