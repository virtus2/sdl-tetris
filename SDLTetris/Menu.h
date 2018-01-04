#ifndef MENU_H
#define MENU_H
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Text.h"
enum MENU
{
	NONE,
	START,
	CLOSE,
};

class Menu
{
	private:
	Text* startText;
	Text* closeText;
	Text* tetrisText;
	Text* textList[3];

	public:
	bool init();
	int run();
	void renderText();
	void close();
	
};

#endif