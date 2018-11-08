#ifndef TextureH
#define TextureH
#include "checkML.h"

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows

#include <string>

using namespace std;

typedef unsigned int uint;

class Texture {
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	uint w = 0; // Texture width
	uint h = 0; // Texture height
	uint fw = 0; // Frame width
	uint fh = 0; // Frame height
	uint numCols = 1;
	uint numRows = 1;

public:
	Texture(SDL_Renderer* r) : renderer(r) {};
	Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer(r) { load(filename, numRows, numCols); };
	~Texture() { clean(); }
	void clean();

	// Gets
	int getW() const { return w; };
	int getH() const { return h; };
	uint getNumCols() const { return numCols; };
	SDL_Texture* getTexture() const { return texture; };

	// Carga de archivo la textura, por defecto con una columna y una fila
	void load(string filename, uint numRows = 1, uint numCols = 1);
	// Carga la textura de un fichero, para dibujarla en la posicion proporcionada en su totalidad
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	// Carga la textura de un fichero, para dibujarla en la posicion proporcionada (uno de sus frames)
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};

#endif
