#include "Game.h"
#include "Menu.h"
#include <cstdio>


Game* game;
Menu* menu;
int main(int argc, char* argv[])
{
	game = new Game();
	menu = new Menu();
	if (!game->init()) return -1;
	if (!menu->init()) return -1;
	while (game->isRunning == true)
	{

		int choose = menu->run();
		if (choose == MENU::START)
		{
			game->gameStart();
		}
		else if (choose == MENU::CLOSE)
		{
			game->isRunning = false;
			break;
		}

		game->gameOver();
		if (menu->gameOver() == false)
		{
			break;
		}
	}
	menu->close();
	game->close();
	return 0;
}