#include "Block.h"
#include "TextureLoader.h"
#include "Game.h"
#include "Board.h"
#include <random>

Block::Block()
{
	std::default_random_engine typeGenerator;
	std::uniform_int_distribution<int> typeDistribution(0, 7);
	std::default_random_engine colorGenerator;
	std::uniform_int_distribution<int> colorDistribution(0, 5);
	//int blockType = typeDistribution(typeGenerator);
	int color = colorDistribution(colorGenerator);
	int blockType = TYPE::O;

	blockPiece[0].pos.xpos = 6;
	blockPiece[0].pos.ypos = 1;
	for (int i = 0; i < 4; i++)
	{
		blockPiece[i].tileType = TILE::BLOCK;
	}
	isActive = true;
	switch (blockType)
	{
		case O:
			blockPiece[1].pos.xpos = 5;
			blockPiece[1].pos.ypos = 1;
			blockPiece[2].pos.xpos = 5;
			blockPiece[2].pos.ypos = 2;
			blockPiece[3].pos.xpos = 6;
			blockPiece[3].pos.ypos = 2;
			lowestPiece = &blockPiece[3];
			break;
		case I:

			break;
		case S:

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
	isActive = true;
}

void Block::fall()
{
	if (isActive)
	{
		for (int i = 0; i < 4; i++)
		{
			blockPiece[i].pos.ypos++;
		}
	}
}
