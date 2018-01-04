#include "Board.h"
#include "TextureLoader.h"
#include "Game.h"

void Board::init()
{
	borderTexture = TextureLoader::loadTexture("asset\\boarder.png");
	emptyTexture = TextureLoader::loadTexture("asset\\empty.png");
	blockTexture = TextureLoader::loadTexture("asset\\block.png");

	srcR.x = 0;
	srcR.y = 0;
	srcR.w = TEXTURE_WIDTH;
	srcR.h = TEXTURE_HEIGHT;
	nextsrc.w = TEXTURE_WIDTH;
	nextsrc.h = TEXTURE_HEIGHT;
	dstR.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2;
	dstR.y = 0;
	dstR.w = BOARD_WIDTH;
	dstR.h = BOARD_HEIGHT;
	dst.w = TEXTURE_WIDTH;
	dst.h = TEXTURE_HEIGHT;
	nextdst.w = TEXTURE_WIDTH;
	nextdst.h = TEXTURE_HEIGHT;

	for (int i = 0; i < 22; i++)
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
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{

		}
	}
}

void Board::draw()
{
	/* test output
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
	*/
	for (int i = 0; i < 22; i++)
	{
		dst.y = 32 + i * TEXTURE_HEIGHT;
		for (int j = 0; j < 12; j++)
		{
			if (tileMap[i][j].tileType == TILE::BORDER)
			{
				dst.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + j * TEXTURE_WIDTH;
				tileMap[i][j].render(borderTexture, &srcR, &dst);
			}
			else if (tileMap[i][j].tileType == TILE::EMPTY)
			{
				dst.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + j * TEXTURE_WIDTH;
				tileMap[i][j].render(emptyTexture, &srcR, &dst);
			}
			else if (tileMap[i][j].tileType == TILE::BLOCK)
			{
				dst.x = SCREEN_WIDTH / 2 - BOARD_WIDTH / 2 + j * TEXTURE_WIDTH;
				tileMap[i][j].render(blockTexture, &srcR, &dst);
			}
		}
	}

}


void Board::setBlockOnMap(Block * block)
{
	for (int i = 0; i < 4; i++)
	{
		tileMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos].tileType = TILE::BLOCK;
	}
}

void Board::drawBlockOnNext(Block * block)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 7)
			{
				nextdst.x = 3 * SCREEN_WIDTH / 4 + j * TEXTURE_WIDTH - 4 * TEXTURE_WIDTH + 32;
				nextdst.y = SCREEN_HEIGHT / 4 + 5 * TEXTURE_HEIGHT + i * TEXTURE_HEIGHT - 8 * TEXTURE_HEIGHT;
				SDL_RenderCopy(Game::renderer, borderTexture, &srcR, &nextdst);
			}
			else
			{
				if (j == 0 || j == 7)
				{
					nextdst.x = 3 * SCREEN_WIDTH / 4 + j * TEXTURE_WIDTH - 4 * TEXTURE_WIDTH + 32;
					nextdst.y = SCREEN_HEIGHT / 4 + 5 * TEXTURE_HEIGHT + i * TEXTURE_HEIGHT - 8 * TEXTURE_HEIGHT;
					SDL_RenderCopy(Game::renderer, borderTexture, &srcR, &nextdst);
				}
			}
		}
	}
	switch (block->blockType)
	{
		case O:
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					nextdst.x = 3 * SCREEN_WIDTH / 4 + i * TEXTURE_WIDTH;
					nextdst.y = SCREEN_HEIGHT / 4 + j * TEXTURE_HEIGHT;
					block->blockPiece[i].render(blockTexture, &nextsrc, &nextdst);
				}
			}
			break;
		case I:
			for (int i = 0; i < 4; i++)
			{
				nextdst.x = 3 * SCREEN_WIDTH / 4 + i * TEXTURE_WIDTH - TEXTURE_WIDTH;
				nextdst.y = SCREEN_HEIGHT / 4;
				block->blockPiece[i].render(blockTexture, &nextsrc, &nextdst);
			}
			break;
		case Z:

			break;
		case L:

			break;
		case J:

			break;
		case T:

			break;
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

void Board::rotateBlock(Block * block)
{
	for (int i = 0; i < 4; i++)
	{
		tileMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos].tileType = EMPTY;
	}
	block->rotate();
}

bool Board::checkLine()
{
	int count;
	bool gameOver = false;
	for (int i = 1; i < 11; i++)
	{
		if (landedMap[1][i].tileType == TILE::BLOCK)
		{
			gameOver = true;
			return gameOver;
		}
	}
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
					removeLine(i);
					for (int k = i; k > 1; k--)
					{
						collapseLine(k);
					}
				}
			}
			else
				break;
		}
	}
	return gameOver;
}

void Board::removeLine(int line)
{
	for (int i = 1; i < 11; i++)
	{
		landedMap[line][i].tileType = TILE::EMPTY;
		tileMap[line][i].tileType = TILE::EMPTY;
	}
}

void Board::collapseLine(int line)
{
	for (int i = 1; i < 11; i++)
	{
		if (landedMap[line - 1][i].tileType == TILE::BLOCK)
		{
			landedMap[line][i].tileType = TILE::BLOCK;
			landedMap[line - 1][i].tileType = TILE::EMPTY;

			tileMap[line][i].tileType = TILE::BLOCK;
			tileMap[line - 1][i].tileType = TILE::EMPTY;
		}
	}
}


void Board::destroy()
{
	SDL_DestroyTexture(borderTexture);
	SDL_DestroyTexture(emptyTexture);
	SDL_DestroyTexture(blockTexture);
}

