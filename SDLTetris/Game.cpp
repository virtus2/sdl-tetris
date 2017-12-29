#include "Game.h"
#include <SDL.h>
#include <cstdio>


Game::Game()
{
}


Game::~Game()
{
}

bool Game::init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize!: %s\n", SDL_GetError());
		success = false;
	}
	else
	{

	}
}
