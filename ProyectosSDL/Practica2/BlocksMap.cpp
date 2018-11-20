#include "BlocksMap.h"
#include "Game.h"

BlocksMap::BlocksMap() :
	ArkanoidObject(), blocks_(nullptr), rows_(0), cols_(0), numBlocks_(0)
{
}

BlocksMap::BlocksMap(Vector2D pos, uint width, uint height, Texture* texture) :
	ArkanoidObject(pos, width, height, texture), blocks_(nullptr), rows_(0), cols_(0), numBlocks_(0)
{
}

BlocksMap::~BlocksMap()
{
	if (blocks_ != nullptr)
	{
		// Elimina cada vector de la matriz
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				delete blocks_[i][j];
			}
			delete[] blocks_[i];
		}
		// Elimina el array princial
		delete[] blocks_;

		blocks_ = nullptr;
	}
}

void BlocksMap::render() const
{
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			if (blocks_[i][j] != nullptr)
				blocks_[i][j]->render();
		}
	}
}

void BlocksMap::loadFromFile(string const& filename)
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
		throw ("Error: no se encuentra el fichero " + filename);
	else
	{
		file >> rows_ >> cols_;
		// Creamos la matriz dinamica
		blocks_ = new Block**[rows_];
		for (int i = 0; i < rows_; i++) {
			blocks_[i] = new Block*[cols_];
		}

		// Inicializamos cada bloque
		int color = 0;
		for (int i = 0; i < rows_; i++) {
			for (int j = 0; j < cols_; j++) {
				file >> color; // [0,6]
				if (color == 0)
					blocks_[i][j] = nullptr;
				else
				{
					double blockWidth = width_ / cols_,
						blockHeight = height_ / rows_;

					blocks_[i][j] = new Block
						({ i * blockWidth,j * blockHeight },    // pos
						blockWidth,                             // width
						blockHeight,                            // height
						color - 1,                              // color
						i, j,                                   // row / col
						texture_);                              // texture
					numBlocks_++;
				}
			}
		}
	}
	file.close();
}

void BlocksMap::saveToFile()
{
}