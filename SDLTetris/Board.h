#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Block.h"
#include "Tile.h"
const int TEXTURE_WIDTH = 32;
const int TEXTURE_HEIGHT = 32;
const int BOARD_WIDTH = 400;
const int BOARD_HEIGHT = 600;


class Board
{
	private:
	SDL_Texture* boarderTexture;
	SDL_Texture* emptyTexture;
	SDL_Texture* blockTexture;
	SDL_Rect srcR;
	SDL_Rect dstR;

	public:
	Board();

	Tile tileMap[22][12];
	Tile landedMap[22][12];
	void draw();
	void destroy();
	void setBlockOnMap(Block* block);
	void clearBlockOnMap(Block* block);
	void moveBlock(Block* block, int key);
	void rotateBlock(Block* block);
	void checkLine();
	void removeLine(int line);
	void collapseLine(int line);
};

