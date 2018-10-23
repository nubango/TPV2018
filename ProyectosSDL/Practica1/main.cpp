/// GRUPO 04
/// Nuria Bango Iglesias
/// Javier Camacho Carrasco

#include "checkML.h"
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // CheckML
	try {
		Game game;
		game.run();
	}
	catch (string& error)
	{
		cout << error << endl;
	}
	return 0;
}