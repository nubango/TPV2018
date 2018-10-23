#include "BlocksMap.h"
#include "Game.h"

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

void BlocksMap::load(string const& filename)
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
		throw ("no se encuentra el fichero " + filename);
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
					blocks_[i][j] = new Block(color - 1, i, j, game_->getTexture(BricksTex));
					blocks_[i][j]->setWidth((WIN_WIDTH - (2 * WALL_WIDTH)) / cols_);
					blocks_[i][j]->setHeight(((WIN_HEIGHT - WALL_WIDTH) / rows_) / 2);
					numBlocks_++;
				}
			}
		}
	}
	file.close();
}

void BlocksMap::render()
{
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			if (blocks_[i][j] != nullptr)
				blocks_[i][j]->render();
		}
	}
}

Block * BlocksMap::collides(Vector2D vecBall)
{
	return nullptr;
}
