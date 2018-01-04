#include "Menu.h"
#include <cstdio>
#include "Game.h"

bool Menu::init()
{
	bool success = true;
	if (TTF_Init() < 0)
	{
		printf("SDL_ttf could not initialize! %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Linear texture filltering not enabled!\n");
		}
		gameFont = TTF_OpenFont("C:\\windows\\fonts\\comic.ttf", 12);
		if (gameFont == NULL)
		{
			printf("Failed to load font!\n");
			success = false;
		}
		SDL_Color textColor = { 255,255,255 };
		SDL_Surface* textSurface = TTF_RenderText_Solid(gameFont, "start", textColor);
		textTexture = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
		SDL_FreeSurface(textSurface);

		

	}


	return success;
}

int Menu::run()
{
	int choose;
	while (!choose)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_KP_ENTER)
				{
					printf("enter");
				}
			}
			else if(event.type == SDL_QUIT)
		}
	}
	return choose;
}

void Menu::renderText()
{

}

void Menu::close()
{

}



