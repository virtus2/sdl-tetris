#pragma once
#include "Coord.h"
#include <SDL_image.h>
enum TILE
{
	EMPTY,
	BORDER,
	BLOCK,
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE,
	PINK,
	PURPLE,
};

class Tile
{
	public:
	Tile();
	int tileType;
	coord pos;

	void render(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst);
};

