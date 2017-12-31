#include "Game.h"
#include <cstdio>
#include "Board.h"

const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;


SDL_Renderer* Game::renderer = NULL;


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
				SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
				if (loadMedia())
				{
					isRunning = true;
					board = new Board();
					block = new Block();
				}
				else
				{
					success = false;
				}
			}
		}

	
	}

	return success;
}

bool Game::loadMedia()
{
	bool success = true;
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize!: %s\n", IMG_GetError());
		success = false;
	}
	return success;
}


void Game::run()
{
	while (isRunning)
	{
		frameStart = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	close();
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event) != 0)
	{
		switch (event.type)
		{
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
		}
	}
}

void Game::update()
{
	board->setBlockOnMap(block);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	board->draw();
	SDL_RenderPresent(renderer);
}

void Game::close()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_Quit();
}
