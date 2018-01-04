#ifndef MENU_H
#define MENU_H
#include <SDL_ttf.h>
#include <SDL.h>
#include <SDL_image.h>
enum MENU
{
	START,
	CLOSE,

};

class Menu
{
	private:
	TTF_Font* gameFont;
	SDL_Texture* textTexture;

	public:
	bool init();
	int run();
	void renderText();
	void close();
	
};

#endif