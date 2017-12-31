#pragma once
#include "Coord.h"
#include <SDL_image.h>
enum TILE
{
	EMPTY,
	BORDER,
	BLOCK,
};

class Tile
{
	public:

	int tileType;
	coord pos;

	void render(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst);
};

