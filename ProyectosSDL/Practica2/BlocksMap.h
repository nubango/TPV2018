#pragma once
#include "ArkanoidObject.h"
#include "Block.h"

class BlocksMap :
	public ArkanoidObject
{
protected:
	Block*** blocks_; // Matriz dinamica de bloques
	uint rows_;
	uint cols_;
	uint numBlocks_;
	double blockWidth_;
	double blockHeight_;

public:
	BlocksMap();
	BlocksMap(Vector2D pos, double width, double height, Texture* texture);
	virtual ~BlocksMap();

	virtual void render() const;

	Block* collidesBlock(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D & collVector);

	// Destruye el bloque (se llama desde Game cuando la bola colisione)
	void hitBlock(Block* block);
	// Para consultar cuantos bloques quedan
	uint getNumBlocks() { return numBlocks_; };

	virtual void loadFromFile(ifstream& file);
	virtual void saveToFile(ofstream& file);

private:
	Block* blockAt(const Vector2D& pos);
};