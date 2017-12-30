#include "Game.h"
#include <cstdio>


Game* game;
int main(int argc, char* argv[])
{
	game = new Game();
	game->init();
	game->run();

	return 0;
}