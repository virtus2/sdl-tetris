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
	// SDL initialize
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize!: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		isRunning = true;
		window = SDL_CreateWindow("SDL Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created!: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Crate renderer for window
			renderer = SDL_CreateRenderer(window, -1, NULL);
			if (renderer == NULL)
			{
				printf("Renderer could not be created!: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}

	
	}

	return success;
}

void Game::run()
{
	while (isRunning)
	{
		handleEvents();
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT: 
			isRunning = false;
			break;
		default: 
			break;
	}
}

void Game::update()
{
}

void Game::render()
{
}

void Game::close()
{
}
