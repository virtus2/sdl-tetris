#include "Text.h"
#include "Game.h"

Text::Text(std::string fontLocation, std::string text, int fontSize, int r, int g, int b)
{
	SDL_Color color = { r, g, b };
	font = TTF_OpenFont(fontLocation.c_str(), fontSize);
	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (tempSurface == NULL)
	{
		printf("Unable to render text surface! %s\n", TTF_GetError());
	}
	textTexture =  SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	if (textTexture == NULL)
	{
		printf("Unable to create texture from rendered text! %s\n", SDL_GetError());
	}
	src.h = tempSurface->h;
	src.w = tempSurface->w;
	SDL_FreeSurface(tempSurface);
}

void Text::render(SDL_Rect* dst)
{
	SDL_RenderCopy(Game::renderer, textTexture, &src, dst);
}

void Text::destroy()
{
	SDL_DestroyTexture(textTexture);
	textTexture = NULL;
	TTF_CloseFont(font);
	font = NULL;
}