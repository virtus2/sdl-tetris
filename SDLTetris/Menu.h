#ifndef MENU_H
#define MENU_H
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Text.h"
const int TEXT_COUNT = 3;
enum MENU
{
	NONE,
	START,
	CLOSE,
};

class Menu
{
	private:
	int menu;
	SDL_Rect dst;
	SDL_Rect arrowDst;
	Text* startText;
	Text* closeText;
	Text* tetrisText;
	Text* arrowText;
	Text* textList[TEXT_COUNT];

	public:
	bool init();
	int run();
	void renderText();
	void close();
	
};

#endif