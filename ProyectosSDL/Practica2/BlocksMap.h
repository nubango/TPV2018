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

	Block* collidesMap(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D & collVector);
	Block* blockAt(const Vector2D& pos);

	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);
};