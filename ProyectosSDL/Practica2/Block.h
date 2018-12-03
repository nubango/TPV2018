#pragma once
#include "ArkanoidObject.h"

class Block :
	public ArkanoidObject
{
protected:
	uint color_, // Entero para encontrar el frame de la textura [0,5]
		row_, // Fila en el mapa de bloques
		col_; // Columna en el mapa de bloques

public:
	Block();
	Block(Vector2D pos, uint width, uint height, uint color, uint row, uint col, Texture* texture);
	virtual ~Block();

	virtual void render() const;

	double getX() { return pos_.getX(); }
	double getY() { return pos_.getY(); }
	uint getW() { return width_; }
	uint getH() { return height_; }

	virtual void loadFromFile(string const& filename) {}
	virtual void saveToFile() {}
};