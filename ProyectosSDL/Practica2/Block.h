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
	virtual ~Block() {};

	virtual void render() const;

	uint getRow() { return row_; }
	uint getCol() { return col_; }
};