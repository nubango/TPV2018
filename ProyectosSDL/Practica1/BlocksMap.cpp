#include "BlocksMap.h"

BlocksMap::~BlocksMap()
{
	// Elimina cada vector de la matriz
	for (int i = 0; i < rows_; i++)
		delete[] blocks_[i];
	// Elimina el vector princial
	delete[] blocks_;
}

void BlocksMap::load(string const& filename)
{
	ifstream file;
	file.open(filename);
	if (!file.is_open())
		cout << "No se encuentra el fichero" << endl;
	else
	{
		while (!file.fail())
		{
			cin >> rows_ >> cols_;
			// Creamos la matriz dinamica
			blocks_ = new Block*[rows_];
			for (int i = 0; i < rows_; i++) {
				blocks_[i] = new Block[cols_];
			}

			// Asociamos los datos a cada bloque
			int color;
			for (int i = 0; i < rows_; i++) {
				for (int j = 0; j < cols_; j++) {
					///cin >> color;
					///blocks_[i][j].setColor(color);
					///blocks_[i][j].setRow(i);
					///blocks_[i][j].setCol(j);
					///blocks_[i][j] = new Block({ i*blockWidth_,j*blockWidth_ }, blockWidth_, blockHeight_, color);
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
			blocks_[i][j].render();
		}
	}
}

int BlocksMap::getblocksLeft()
{
	int numBlocks = 0;
	for (int i = 0; i < rows_; i++) {
		for (int j = 0; j < cols_; j++) {
			if (blocks_[i][j].getColor() != 0)
				numBlocks++;
		}
	}
	return numBlocks;
}