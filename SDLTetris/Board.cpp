#include "Board.h"
#include "TextureLoader.h"

Board::Board()
{
	boarderTexture = TextureLoader::loadTexture("asset\\boarder.png");
	emptyTexture = TextureLoader::loadTexture("asset\\empty.png");

	srcR.x = 0;
	srcR.y = 0;
	srcR.w = TEXTURE_WIDTH;
	srcR.h = TEXTURE_HEIGHT;
	dstR.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2;
	dstR.y = 0;
	dstR.w = BOARD_WIDTH;
	dstR.h = BOARD_HEIGHT;
}


Board::~Board()
{
}

void Board::draw()
{
	SDL_RenderCopy(Game::renderer, boarderTexture, &srcR, &dstR);
}

void Board::destroy()
{
	SDL_DestroyTexture(boarderTexture);
	SDL_DestroyTexture(emptyTexture);
}
