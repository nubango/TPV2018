#pragma once
#include "SDLApp.h"
#include "Texture.h"
#include "Button.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

class Game :
	public SDLApp
{
public:
	static const uint UI_WIDTH = 200;
	static const uint FRAME_RATE = 60;
	static const uint WALL_SIZE = 20;

	static const std::string IMAGE_PATH;
	static const std::string LEVEL_PATH;
	static const std::string FONT_PATH;
	static const std::string CONFIG_PATH;
	static const std::string FILE_EXTENSION;

private:
	static bool exit_;

	Button* button_;

	static GameStateMachine* gsm_;

	std::map<std::string, Texture*> textures_;
	std::map<std::string, Font*> fonts_;

	void handleEvent();
	void update();
	void render();

	void initResources();
	void closeResources();
	void initGame();
	void closeGame();

public:
	Game();
	virtual ~Game();

	void run();

	Texture* getTexture(std::string key) { return textures_[key]; }
	Font* getFont(std::string key) { return fonts_[key]; }

	static void toPlayState(Game* g);
	static void toPauseState(Game* g);
	static void resumePlayState(Game* g);
	static void toEndState(Game* g);
	static void toMenuState(Game* g);
	static void exit(Game* g);
};