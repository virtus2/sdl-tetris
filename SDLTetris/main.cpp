#include "Game.h"
#include "Menu.h"
#include <cstdio>


Game* game;
Menu* menu;
int main(int argc, char* argv[])
{
	game = new Game();
	if (game->init())
	{
		game->run();
	}

	return 0;
}