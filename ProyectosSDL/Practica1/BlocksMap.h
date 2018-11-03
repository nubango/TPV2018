#pragma once
#include "Block.h"
#include <fstream>

class Game;

class BlocksMap
{
private:
	Block*** blocks_ = nullptr; // Matriz dinamica de bloques
	uint rows_ = 0,
		cols_ = 0,
		height_ = 0,
		width_ = 0,
		numBlocks_ = 0;

	Game* game_ = nullptr;
	Texture* texture_ = nullptr;

public:
	BlocksMap(uint height, uint width, Game* game);
	~BlocksMap();

	// Para consultar cuantos bloques quedan
	uint getNumBlocks() { return numBlocks_; };
	// Devuelve la posicion inferior del mapa de bloques
	uint getBottomLimit();

	// Destruye el bloque (se llama desde Game cuando la bola colisione)
	void hitBlock(Block* block) { block = nullptr; }

	// Carga de fichero el mapa
	void load(string const& filename);
	// Renderiza los bloques
	void render();
	// Dados el rectangulo y vector de direccion de la pelota, devuelve un puntero al bloque con el que 
	// esta colisiona (nullptr si no colisiona con nadie) y el vector normal perpendicular a la superficie de colisión.
	Block* collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D & collVector);
	// Devuelve el puntero al bloque del mapa de bloques al que pertenece el punto p
	Block* blockAt(const Vector2D& pos);
};