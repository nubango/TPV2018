#include "checkML.h"
#include "Game.h"

int main(int argc, char* argv[]) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Memory Leaks
	try
	{
		Game game;
		game.run();
	}
	catch (ArkanoidError& error)
	{
		cout << &error << endl;
	}
	return 0;
}