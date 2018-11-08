#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "Texture.h"

typedef unsigned int uint;

class Block
{
private:
	Vector2D pos_ = { 0,0 };
	uint width_ = 0,
		height_ = 0;
	Texture* texture_ = nullptr;

	uint color_, // Entero para encontrar el frame de la textura [0,5]
		row_, // Fila en el mapa de bloques
		col_; // Columna en el mapa de bloques

public:
	Block(uint color, uint row, uint col, Texture* texture);
	~Block() {}

	void setWidth(uint width) { width_ = width; }
	void setHeight(uint height) { height_ = height; }
	void setColor(uint color) { color_ = color; }

	double getX() { return pos_.getX(); }
	double getY() { return pos_.getY(); }
	uint getW() { return width_; }
	uint getH() { return height_; }

	// Dibuja el bloque en pantalla
	void render();
};