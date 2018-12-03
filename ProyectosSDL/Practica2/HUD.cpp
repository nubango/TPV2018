#include "HUD.h"
#include "Game.h"

HUD::HUD() : logoTexture_(nullptr), livesTexture_(nullptr), game_(nullptr), numLives_(0)
{
}

HUD::HUD(Vector2D pos, uint width, uint height, Texture * logoTexture) : ArkanoidObject(pos, width, height, logoTexture)
{
	numLives_ = game_->getLives(); //  Se coge el numero de vidas al principio del juego para calcular el espacio que se va a usar

}

HUD::~HUD()
{
}

void HUD::render()
{
	// Renderizamos el logo
	/// NO SE PUEDE USAR EL ARKANOID::RENDER() ???? PORQUE CLARO, HEIGHT NO ES DEL HUD, ES DEL LOGO?
	/// CLASES HIJAS PARA CADA ELEMENTO DEL HUD???
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,Game::LOGO_HEIGHT };
	logoTexture_->render(destRect);

	// Renderizamos las vidas
	// Dependiendo del numero de vidas iniciales se divide el espacio del HUD
	uint margen = 10;
	// Se actualiza al perder vidas con game_->getLives()
	int hudWidth = Game::WIN_WIDTH_PLUS_HUD - Game::WIN_WIDTH;
	for (int i = 0; i < game_->getLives(); i++) {
		SDL_Rect destRect = {
			pos_.getX() + (i * (hudWidth) / numLives_) + (margen / 2), // X
			pos_.getY() + Game::LOGO_HEIGHT + margen,                  // Y
			(hudWidth / numLives_) - margen,                           // W
			Game::PADDLE_HEIGHT };                                     // H
		livesTexture_->render(destRect);
	}
}