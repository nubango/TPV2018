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

Block * BlocksMap::collidesMap(const SDL_Rect & ballRect, const Vector2D & ballVel, Vector2D & collVector)
{
	Vector2D p0 = Vector2D(ballRect.x, ballRect.y); // top-left
	Vector2D p1 = Vector2D(ballRect.x + ballRect.w, ballRect.y); // top-right
	Vector2D p2 = Vector2D(ballRect.x, ballRect.y + ballRect.h); // bottom-left
	Vector2D p3 = Vector2D(ballRect.x + ballRect.w, ballRect.y + ballRect.h); // bottom-right
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
	if (pos.getX() > Game::WALL_SIZE && pos.getX() < Game::WIN_WIDTH - Game::WALL_SIZE &&
		pos.getY() > Game::WALL_SIZE && pos.getY() < height_ + Game::WALL_SIZE)
	{
		// Dividimos la posicion relativa al blocksMap entre el ancho o alto del bloque
		double bWidth = width_ / cols_,
			bHeight = height_ / rows_;

		int nCol = trunc((pos.getX() - Game::WALL_SIZE) / bWidth);
		int nRow = trunc((pos.getY() - Game::WALL_SIZE) / bHeight);

		// Devuelve nullptr si no hay bloque o el bloque si existe
		return blocks_[nRow][nCol];
	}
	else
		// Devuelve nullptr si esta fuera del espacio del mapa
		return nullptr;
}

void BlocksMap::loadFromFile(ifstream & file)
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
				({ i * blockWidth,j * blockHeight },        // pos
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

void BlocksMap::saveToFile(ofstream& file)
{
}