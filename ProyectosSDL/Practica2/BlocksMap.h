#pragma once
#include "ArkanoidObject.h"
#include "Block.h"

class BlocksMap :
	public ArkanoidObject
{
protected:
	Block*** blocks_; // Matriz dinamica de bloques
	uint rows_,
		cols_,
		numBlocks_;

public:
	BlocksMap();
	BlocksMap(Vector2D pos, uint width, uint height, Texture* texture);
	virtual ~BlocksMap();

	virtual void render() const;

	virtual void loadFromFile(string const& filename);
	virtual void saveToFile();
};