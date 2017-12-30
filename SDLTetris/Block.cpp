#include "Block.h"
#include "TextureLoader.h"
#include "Game.h"
#include <random>

void Block::init()
{
	std::default_random_engine typeGenerator;
	std::uniform_int_distribution<int> typeDistribution(0, 7);
	std::default_random_engine colorGenerator;
	std::uniform_int_distribution<int> colorDistribution(0, 5);
	int blockType = typeDistribution(typeGenerator);
	int color = colorDistribution(colorGenerator);
	
	switch (color)
	{
		case RED: 
			blockTexture = TextureLoader::loadTexture("block.png");
			break;
		default:
			blockTexture = TextureLoader::loadTexture("block.png");
			break;
	}

	switch (blockType)
	{
		case O:
			orientX = 6;
			orientX = 20;
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

void Block::update()
{
	if (isActive)
	{

	}
}

void Block::render(SDL_Rect src, SDL_Rect dst)
{
	SDL_RenderCopy(Game::renderer, blockTexture, &src, &dst);
}
