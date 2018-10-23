/// Contiene el mapa de bloques del juego

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
	BlocksMap() {}
	BlocksMap(uint height, uint width, Game* game) :
		height_(height), width_(width), game_(game) {}
	~BlocksMap();

	// Para consultar cuantos bloques quedan
	uint getblocksLeft() { return numBlocks_; };

	// Carga de fichero el mapa
	void load(string const& filename);
	// Renderiza los bloques
	void render();
	// Determina el bloque y el vector de colision
	Block* collides(Vector2D vecBall);
};