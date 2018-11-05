#include "HUD.h"
#include "Game.h"

HUD::HUD(Vector2D pos, uint width, uint height, Texture * livesTexture, Texture* logoTexture, Texture* timerTexture, Game * game) :
	pos_(pos), width_(width), height_(height), livesTexture_(livesTexture), logoTexture_(logoTexture), timerTexture_(timerTexture), game_(game)
{
	timer_ = new Timer({ pos_.getX(), height_ / 2.0 }, width_, height_ / 20.0, timerTexture_);
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
	// Se actualiza a� perder vidas con game_->getLives()
	int numLives = game_->getLives();
	for (int i = 0; i < game_->getLives(); i++) {
		SDL_Rect destRect = { pos_.getX() + (i * (WIN_WIDTH_PLUS_HUD - WIN_WIDTH) / numLives),
			pos_.getY() + LOGO_HEIGHT + 10,
			(WIN_WIDTH_PLUS_HUD - WIN_WIDTH) / numLives,
			PADDLE_HEIGHT };
		livesTexture_->render(destRect);
	}

	// Renderizamos el timer
	timer_->render();
}

void HUD::update()
{
	timer_->update();
}