#include "TextureLoader.h"
#include "Game.h"

SDL_Texture* TextureLoader::loadTexture(std::string path)
{
	SDL_Surface* tempSurface = IMG_Load(path.c_str());
	SDL_Texture* loadedTexture;
	if (tempSurface == NULL)
	{
		printf("image could not be loaded!: %s\n", IMG_GetError());
	}
	loadedTexture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	return loadedTexture;
}


