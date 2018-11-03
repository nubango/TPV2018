#include "BlocksMap.h"
#include "Game.h"

BlocksMap::BlocksMap(uint height, uint width, Game * game) :
	height_(height), width_(width), game_(game)
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

uint BlocksMap::getBottomLimit()
{
	return (WIN_HEIGHT / 2) - WALL_WIDTH;
}

void BlocksMap::load(string const& filename)
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

Block * BlocksMap::collides(const SDL_Rect& ballRect, const Vector2D& ballVel, Vector2D & collVector)
{
	Vector2D p0 = { (double)ballRect.x, (double)ballRect.y }; // top-left
	Vector2D p1 = { (double)ballRect.x + (double)ballRect.w, (double)ballRect.y }; // top-right
	Vector2D p2 = { (double)ballRect.x, (double)ballRect.y + (double)ballRect.h }; // bottom-left
	Vector2D p3 = { (double)ballRect.x + (double)ballRect.w, (double)ballRect.y + (double)ballRect.h }; // bottom-right
	Block* b = nullptr;
	if (ballVel.getX() < 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p0))) {
			if ((b->getY() + b->getH() - p0.getY()) <= (b->getX() + b->getW() - p0.getX()))
				collVector = { 0,1 }; // Borde inferior mas cerca de p0
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p1))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p2))) collVector = { 1,0 };
	}
	else if (ballVel.getX() >= 0 && ballVel.getY() < 0) {
		if ((b = blockAt(p1))) {
			if (((b->getY() + b->getH() - p1.getY()) <= (p1.getX() - b->getX())) || ballVel.getX() == 0)
				collVector = { 0,1 }; // Borde inferior mas cerca de p1
			else
				collVector = { -1,0 }; // Borde izqdo mas cerca de p1
		}
		else if ((b = blockAt(p0))) {
			collVector = { 0,1 };
		}
		else if ((b = blockAt(p3))) collVector = { -1,0 };
	}
	else if (ballVel.getX() > 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p3))) {
			if (((p3.getY() - b->getY()) <= (p3.getX() - b->getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p3
			else
				collVector = { -1,0 }; // Borde dcho mas cerca de p3
		}
		else if ((b = blockAt(p2))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p1))) collVector = { -1,0 };
	}
	else if (ballVel.getX() < 0 && ballVel.getY() > 0) {
		if ((b = blockAt(p2))) {
			if (((p2.getY() - b->getY()) <= (b->getX() + b->getW() - p2.getX()))) // || ballVel.getX() == 0)
				collVector = { 0,-1 }; // Borde superior mas cerca de p2
			else
				collVector = { 1,0 }; // Borde dcho mas cerca de p0
		}
		else if ((b = blockAt(p3))) {
			collVector = { 0,-1 };
		}
		else if ((b = blockAt(p0))) collVector = { 1,0 };
	}
	return b;
}

Block * BlocksMap::blockAt(const Vector2D & pos)
{
	// Conseguimos el ancho o alto de cada bloque y dividimos pos entre ese valor
	int nRow = (int)pos.getX() / (width_ / rows_);
	int nCol = (int)pos.getY() / (height_ / cols_);

	// En caso de no haber bloque en ese punto devuelve nullptr
	// (incluido el caso de que p esté fuera del espacio del mapa) 
	if (nRow > (getBottomLimit() / (width_ / rows_)))
		return nullptr;
	if (nCol < 0 && nCol > WIN_WIDTH)
		return nullptr;
	else
		return blocks_[nRow][nCol];
}