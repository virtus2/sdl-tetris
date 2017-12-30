#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class TextureLoader
{
	public:
	static SDL_Texture* loadTexture(std::string path);
};

