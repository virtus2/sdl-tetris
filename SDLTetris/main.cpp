#include "Game.h"
#include <cstdio>

int main(int argc, char* argv[])
{
	Game* game = new Game();
	game->init();
	game->run();

	return 0;
}