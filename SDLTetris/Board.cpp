#include "Board.h"
#include "TextureLoader.h"
#include "Game.h"

Board::Board()
{
	boarderTexture = TextureLoader::loadTexture("asset\\boarder.png");
	emptyTexture = TextureLoader::loadTexture("asset\\empty.png");
	blockTexture = TextureLoader::loadTexture("asset\\block.png");

	srcR.x = 0;
	srcR.y = 0;
	srcR.w = TEXTURE_WIDTH;
	srcR.h = TEXTURE_HEIGHT;
	dstR.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2;
	dstR.y = 0;
	dstR.w = BOARD_WIDTH;
	dstR.h = BOARD_HEIGHT;

	for(int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			tileMap[i][j].pos.xpos = j;
			tileMap[i][j].pos.ypos = i;
			landedMap[i][j].pos.xpos = j;
			landedMap[i][j].pos.ypos = i;
			if (i == 0 || i == 21)
			{
				tileMap[i][j].tileType = TILE::BORDER;
				landedMap[i][j].tileType = TILE::BORDER;
			}
			if (j == 0 || j == 11)
			{
				tileMap[i][j].tileType = TILE::BORDER;
				landedMap[i][j].tileType = TILE::BORDER;
			}
			
		}
	}
}


void Board::draw()
{
	SDL_Rect dst;
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (landedMap[i][j].tileType == TILE::BORDER)
			{
				dst.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + j * TEXTURE_WIDTH;
				dst.y = 32 + i * TEXTURE_HEIGHT;
				dst.w = TEXTURE_WIDTH;
				dst.h = TEXTURE_HEIGHT;
				landedMap[i][j].render(boarderTexture, &srcR, &dst);
			}
			else if (landedMap[i][j].tileType == TILE::EMPTY)
			{
				dst.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + j * TEXTURE_WIDTH;
				dst.y = 32 + i * TEXTURE_HEIGHT;
				dst.w = TEXTURE_WIDTH;
				dst.h = TEXTURE_HEIGHT;
				landedMap[i][j].render(emptyTexture, &srcR, &dst);
			}
			else if (landedMap[i][j].tileType == TILE::BLOCK)
			{
				dst.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + j * TEXTURE_WIDTH;
				dst.y = 32 + i * TEXTURE_HEIGHT;
				dst.w = TEXTURE_WIDTH;
				dst.h = TEXTURE_HEIGHT;
				landedMap[i][j].render(blockTexture, &srcR, &dst);
			}
		}
	}
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (tileMap[i][j].tileType == TILE::BORDER)
			{
				dst.x = j * TEXTURE_WIDTH;
				dst.y = 32 + i * TEXTURE_HEIGHT;
				dst.w = TEXTURE_WIDTH;
				dst.h = TEXTURE_HEIGHT;
				tileMap[i][j].render(boarderTexture, &srcR, &dst);
			}
			else if (tileMap[i][j].tileType == TILE::EMPTY)
			{
				dst.x = j * TEXTURE_WIDTH;
				dst.y = 32 + i * TEXTURE_HEIGHT;
				dst.w = TEXTURE_WIDTH;
				dst.h = TEXTURE_HEIGHT;
				tileMap[i][j].render(emptyTexture, &srcR, &dst);
			}
			else if (tileMap[i][j].tileType == TILE::BLOCK)
			{
				dst.x = j * TEXTURE_WIDTH;
				dst.y = 32 + i * TEXTURE_HEIGHT;
				dst.w = TEXTURE_WIDTH;
				dst.h = TEXTURE_HEIGHT;
				tileMap[i][j].render(blockTexture, &srcR, &dst);
			}
		}
	}
}

void Board::update()
{

}

void Board::setBlockOnMap(Block * block)
{
	for (int i = 0; i < 4; i++)
	{
		tileMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos].tileType = TILE::BLOCK;
	}
}

void Board::clearBlockOnMap(Block * block)
{
	for (int i = 0; i < 4; i++)
	{
		tileMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos].tileType = TILE::EMPTY;
	}
}

void Board::moveBlock(Block* block, int key)
{
	Block* temp = block;
	switch (key)
	{
		case SDLK_LEFT:
			for (int i = 0; i < 4; i++)
			{
				tileMap[temp->blockPiece[i].pos.ypos][temp->blockPiece[i].pos.xpos].tileType = TILE::EMPTY;
				temp->blockPiece[i].pos.xpos--;
			}
			break;
		case SDLK_RIGHT:
			for (int i = 0; i < 4; i++)
			{
				tileMap[temp->blockPiece[i].pos.ypos][temp->blockPiece[i].pos.xpos].tileType = TILE::EMPTY;
				temp->blockPiece[i].pos.xpos++;
			}
			break;
	}
}

void Board::checkLine()
{
	int count;
	for (int i = 1; i < 21; i++)
	{
		count = 0;
		for (int j = 1; j < 11; j++)
		{
			if (landedMap[i][j].tileType == TILE::BLOCK)
			{
				count++;
				if (count == 10)
				{
					for (int k = 1; k < 11; k++)
					{
						landedMap[i][k].tileType = TILE::EMPTY;
						tileMap[i][k].tileType = TILE::EMPTY;
						
					}
					collapseLine(i);
				}
			}
			else
				break;
		}
	}
}

void Board::collapseLine(int line)
{
	for (int i = 1; i < line; i++)
	{
		for (int j = 1; j < 11; j++)
		{
			if (landedMap[i][j].tileType == TILE::BLOCK)
			{
				landedMap[i][j].tileType = TILE::EMPTY;
				tileMap[i][j].tileType = TILE::EMPTY;
				landedMap[i + 1][j].tileType = TILE::BLOCK;
				tileMap[i + 1][j].tileType = TILE::BLOCK;
			}
		}
	}
}


void Board::destroy()
{
	SDL_DestroyTexture(boarderTexture);
	SDL_DestroyTexture(emptyTexture);
	SDL_DestroyTexture(blockTexture);
}

