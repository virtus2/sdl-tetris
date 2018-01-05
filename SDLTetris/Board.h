#ifndef BOARD_H
#define BOARD_H
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
	SDL_Texture* borderTexture;
	SDL_Texture* emptyTexture;
	SDL_Texture* blockTexture;
	SDL_Texture* redBlockTexture;
	SDL_Texture* orangeBlockTexture;
	SDL_Texture* yellowBlockTexture;
	SDL_Texture* greenBlockTexture;
	SDL_Texture* blueBlockTexture;
	SDL_Texture* pinkBlockTexture;
	SDL_Texture* purpleBlockTexture;

	SDL_Rect srcR;
	SDL_Rect dstR;
	SDL_Rect dst;
	SDL_Rect nextsrc;
	SDL_Rect nextdst;

	public:
	

	Tile tileMap[22][12];
	Tile landedMap[22][12];
	int nextMap[6][6] = 
	{ 
		1,1,1,1,1,1,
		1,0,0,0,0,1,
		1,0,0,0,0,1,
		1,0,0,0,0,1,
		1,0,0,0,0,1,
		1,1,1,1,1,1,
	};
	void init();
	void draw();
	void destroy();
	void setBlockOnMap(Block* block);
	void drawBlockOnNext(Block* block);
	void clearBlockOnMap(Block* block);
	void moveBlock(Block* block, int key);
	void rotateBlock(Block* block);
	bool checkLine(int& score);
	void removeLine(int line);
	void collapseLine(int line);
};
#endif /* BOARD_H */

