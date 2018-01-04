#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
class Text
{
	private:
	TTF_Font* font;
	SDL_Texture* textTexture;
	SDL_Rect src;

	public:
	Text(std::string fontLocation, std::string text, int fontSize, int r, int g, int b);
	Text();
	int getWidth() { return src.w; };
	int getHeight() { return src.h; };
	void render(SDL_Rect *dst);
	void destroy();
};

