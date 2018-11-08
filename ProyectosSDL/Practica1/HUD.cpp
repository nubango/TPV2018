#include "HUD.h"
#include "Game.h"

HUD::HUD(Vector2D pos, uint width, uint height, Texture * livesTexture, Texture* logoTexture, Texture* timerTexture, Game * game) :
	pos_(pos), width_(width), height_(height), livesTexture_(livesTexture), logoTexture_(logoTexture), timerTexture_(timerTexture), game_(game)
{
	timer_ = new Timer({ pos_.getX(), height_ / 2.0 }, width_, height_ / 20.0, timerTexture_);
	numLives_ = game_->getLives(); //  Se coge el numero de vidas al principio del juego para calcular el espacio que se va a usar
}

HUD::~HUD()
{
	delete timer_;
}

void HUD::render()
{
	// Renderizamos el logo
	SDL_Rect destRect = { pos_.getX(),pos_.getY(),width_,LOGO_HEIGHT };
	logoTexture_->render(destRect);

	// Renderizamos las vidas
	// Dependiendo del numero de vidas iniciales se divide el espacio del HUD
	uint margen = 10;
	// Se actualiza al perder vidas con game_->getLives()
	int hudWidth = WIN_WIDTH_PLUS_HUD - WIN_WIDTH;
	for (int i = 0; i < game_->getLives(); i++) {
		SDL_Rect destRect = {
			pos_.getX() + (i * (hudWidth) / numLives_) + (margen / 2), // X
			pos_.getY() + LOGO_HEIGHT + margen,                        // Y
			(hudWidth / numLives_) - margen,                           // W
			PADDLE_HEIGHT };                                           // H
		livesTexture_->render(destRect);
	}

	// Renderizamos el timer
	timer_->render();
}

void HUD::update()
{
	
}