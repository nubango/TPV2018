/// Representa a los bloques del juego

#pragma once
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Block
{
private:
	Vector2D absolutePos_ = { 0,0 };
	uint width_ = 0,
		height_ = 0;
	Texture* texture_ = nullptr;

	uint color_, // Entero para encontrar el frame de la textura [0,5]
		row_, // Fila en el mapa de bloques
		col_; // Columna en el mapa de bloques

public:
	Block() {}
	Block(uint color, uint row, uint col, Texture* texture) :
		color_(color), row_(row), col_(col), texture_(texture) {}
	~Block() {}

	void setWidth(uint width) { width_ = width; }
	void setHeight(uint height) { height_ = height; }

	// Dibuja el bloque en pantalla
	void render();
};

