#ifndef TextureH
#define TextureH
#include "checkML.h"

#include "SDL.h" // Windows
#include "SDL_image.h" // Windows
#include "Font.h"

#include <string>

using namespace std;

typedef unsigned int uint;

class Texture {
private:
	SDL_Texture* texture_ = nullptr;
	SDL_Renderer* renderer_ = nullptr;
	uint width_ = 0; // Texture width
	uint height_ = 0; // Texture height
	uint frameWidth_ = 0; // Frame width
	uint frameHeight_ = 0; // Frame height
	uint numCols_ = 1;
	uint numRows_ = 1;

public:
	Texture(SDL_Renderer* r) : renderer_(r) {};
	Texture(SDL_Renderer* r, string filename, uint numRows = 1, uint numCols = 1) : renderer_(r) { load(filename, numRows, numCols); };
	~Texture() { clean(); }
	void clean();

	// Gets
	int getW() const { return width_; };
	int getH() const { return height_; };
	uint getNumCols() const { return numCols_; };
	SDL_Texture* getTexture() const { return texture_; };

	// Carga de archivo la textura, por defecto con una columna y una fila
	void load(string filename, uint numRows = 1, uint numCols = 1);
	// Carga la textura de un fichero, para dibujarla en la posicion proporcionada en su totalidad
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	// Carga la textura de un fichero, para dibujarla en la posicion proporcionada (uno de sus frames)
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	
	void loadFont(std::string text, const Font * font, const SDL_Color colour);
};

#endif