/// Contiene el mapa de bloques del juego

#pragma once

#include "Block.h"
#include <fstream>

class BlocksMap
{
private:
	Block** blocks_;
	uint rows_,
		cols_,
		height_,
		width_,
		blockHeight_,
		blockWidth_;

public:
	BlocksMap() {}
	~BlocksMap();

	// Carga de fichero el mapa
	void load(string const& filename);
	// Renderiza los bloques
	void render();
	// Para consultar cuantos bloques quedan
	int getblocksLeft();
	// Determina el bloque y el vector de colision
	///Block* collides(Vector2D vecBall);
};