#include "Block.h"
#include "TextureLoader.h"
#include "Game.h"
#include "Board.h"
#include <ctime>

Block::Block()
{
	std::srand(std::time(nullptr));
	int randomBlock = std::rand() % 7;
	int randomColor = std::rand() % 3;
	blockType = randomBlock;
	color = randomColor; 
	rotateType = 0;
}

void Block::init()
{

	for (int i = 0; i < 4; i++)
	{
		blockPiece[i].tileType = TILE::BLOCK;
	}
	printf("block type is %d\n", blockType);
	isActive = true;
	switch (blockType)
	{
		case O:
			/*
			*  10  O block
			*  23
			*/
			
			blockPiece[0].pos.xpos = 6;
			blockPiece[0].pos.ypos = 1;
			blockPiece[1].pos.xpos = 5;
			blockPiece[1].pos.ypos = 1;
			blockPiece[2].pos.xpos = 5;
			blockPiece[2].pos.ypos = 2;
			blockPiece[3].pos.xpos = 6;
			blockPiece[3].pos.ypos = 2;
			break;
		case I:
			/*
			*	0123 I block
			*
			*/
			blockPiece[0].pos.xpos = 4;
			blockPiece[0].pos.ypos = 1;
			blockPiece[1].pos.xpos = 5;
			blockPiece[1].pos.ypos = 1;
			blockPiece[2].pos.xpos = 6;
			blockPiece[2].pos.ypos = 1;
			blockPiece[3].pos.xpos = 7;
			blockPiece[3].pos.ypos = 1;
			break;
		case S:
			/*
			*	 23 S block
			*	01
			*/
			blockPiece[0].pos.xpos = 5;
			blockPiece[0].pos.ypos = 2;
			blockPiece[1].pos.xpos = 6;
			blockPiece[1].pos.ypos = 2;
			blockPiece[2].pos.xpos = 6;
			blockPiece[2].pos.ypos = 1;
			blockPiece[3].pos.xpos = 7;
			blockPiece[3].pos.ypos = 1;
			break;
		case Z:
			/*
			*	01
			*	 23 Z block
			*/
			blockPiece[0].pos.xpos = 5;
			blockPiece[0].pos.ypos = 1;
			blockPiece[1].pos.xpos = 6;
			blockPiece[1].pos.ypos = 1;
			blockPiece[2].pos.xpos = 6;
			blockPiece[2].pos.ypos = 2;
			blockPiece[3].pos.xpos = 7;
			blockPiece[3].pos.ypos = 2;
			break;
		case L:
			/*
			*	123 L block
			*	0
			*/
			blockPiece[0].pos.xpos = 5;
			blockPiece[0].pos.ypos = 2;
			blockPiece[1].pos.xpos = 5;
			blockPiece[1].pos.ypos = 1;
			blockPiece[2].pos.xpos = 6;
			blockPiece[2].pos.ypos = 1;
			blockPiece[3].pos.xpos = 7;
			blockPiece[3].pos.ypos = 1;
			break;
		case J:
			/*
			*	012 J block
			*	  3
			*/
			blockPiece[0].pos.xpos = 5;
			blockPiece[0].pos.ypos = 1;
			blockPiece[1].pos.xpos = 6;
			blockPiece[1].pos.ypos = 1;
			blockPiece[2].pos.xpos = 7;
			blockPiece[2].pos.ypos = 1;
			blockPiece[3].pos.xpos = 7;
			blockPiece[3].pos.ypos = 2;
			break;
		case T:
			/*
			*	012 T block
			*	 3
			*/
			blockPiece[0].pos.xpos = 5;
			blockPiece[0].pos.ypos = 1;
			blockPiece[1].pos.xpos = 6;
			blockPiece[1].pos.ypos = 1;
			blockPiece[2].pos.xpos = 7;
			blockPiece[2].pos.ypos = 1;
			blockPiece[3].pos.xpos = 6;
			blockPiece[3].pos.ypos = 2;
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