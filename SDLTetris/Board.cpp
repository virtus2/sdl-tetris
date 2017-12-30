#include "Board.h"
#include "TextureLoader.h"
#include "Game.h"

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
	SDL_Rect dst;
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (boardArr[i][j] == TILE::BORDER)
			{
				dst.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + j * TEXTURE_WIDTH;
				dst.y = 32 + i * TEXTURE_HEIGHT;
				dst.w = TEXTURE_WIDTH;
				dst.h = TEXTURE_HEIGHT;
				SDL_RenderCopy(Game::renderer, boarderTexture, &srcR, &dst);
			}
			else if (boardArr[i][j] == TILE::EMPTY)
			{
				dst.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + j * TEXTURE_WIDTH;
				dst.y = 32 + i * TEXTURE_HEIGHT;
				dst.w = TEXTURE_WIDTH;
				dst.h = TEXTURE_HEIGHT;
				SDL_RenderCopy(Game::renderer, emptyTexture, &srcR, &dst);
			}
			else if (boardArr[i][j] == TILE::BLOCK)
			{

			}
		}
	}
}

void Board::destroy()
{
	SDL_DestroyTexture(boarderTexture);
	SDL_DestroyTexture(emptyTexture);
}
