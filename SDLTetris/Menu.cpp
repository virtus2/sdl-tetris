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
			success = false;
			return success;
		}
		startText = new Text("asset\\FFFFORWA.TTF", "START", 20, 255, 255, 255);
		closeText = new Text("asset\\FFFFORWA.TTF", "CLOSE", 20, 255, 255, 255);
		tetrisText = new Text("asset\\FFFFORWA.TTF", "T E T R I S", 36, 255, 0, 0);
		for (int i = 0; i < 3; i++)
		{
			if (textList[i] == NULL)
			{
				success = false;
				return success;
			}
		}
	}


	return success;
}

int Menu::run()
{
	int choose = MENU::NONE;
	int menu = MENU::START;
	while (choose == MENU::NONE)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_RETURN)
				{
					choose = menu;
				}
				if (event.key.keysym.sym == SDLK_DOWN)
				{
					menu == MENU::START ? menu = MENU::CLOSE : menu = MENU::START;
				}
				if (event.key.keysym.sym == SDLK_UP)
				{
					menu == MENU::START ? menu = MENU::CLOSE : menu = MENU::START;
				}
			}
			else if (event.type == SDL_QUIT)
				choose = MENU::CLOSE;
		}
		SDL_RenderClear(Game::renderer);
		renderText();
		SDL_RenderPresent(Game::renderer);
	}
	return choose;
}

void Menu::renderText()
{
	SDL_Rect dst;
	dst.h = startText->getHeight();
	dst.w = startText->getWidth();
	for (int i = 0; i < 3; i++)
	{
		dst.h = textList[i]->getHeight();
		dst.w = textList[i]->getWidth();
		textList[i]->render(&dst);
	}
}

void Menu::close()
{
	for (int i = 0; i < 3; i++)
	{
		textList[i]->destroy();
	}

}



