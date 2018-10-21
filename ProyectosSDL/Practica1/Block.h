/// Representa a los bloques del juego

#pragma once
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Block
{
private:
	Vector2D absolutePos_; // (0,0)
	uint width_ = 0,
		height_ = 0;
	Texture* texture_ = nullptr;

	uint color_, // Entero para encontrar el frame de la textura
		row_, // Fila en el mapa de bloques
		col_; // Columna en el mapa de bloques

public:
	Block() {}
	Block(Vector2D absolutePos, uint width, uint height, Texture* texture) :
		absolutePos_(absolutePos), width_(width), height_(height), texture_(texture) {}
	~Block() {}

	// Sets
	void setColor(uint color) { color_ = color; }
	void setRow(uint row) { row_ = row; }
	void setCol(uint col) { col_ = col; }

	// Gets
	uint getColor() { return color_; }
	uint getWidth() { return width_; }
	uint getHeight() { return height_; }

	void colorAbsolutePosition(uint color);
	// Dibuja el bloque en pantalla
	void render();
};

