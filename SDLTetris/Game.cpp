#include "Game.h"
#include <cstdio>
#include "Board.h"
#include "Tile.h"
#include "Menu.h"
#include "Text.h"

const int FPS = 60;
const int frameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

int fallStart;
int currentTime;
int fallCount;
int level;
SDL_Renderer* Game::renderer = NULL;

bool Game::init()
{
	bool success = true;
	// SDL initialize
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize!: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("SDL Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created!: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Crate renderer for window
			renderer = SDL_CreateRenderer(window, -1, NULL);
			if (renderer == NULL)
			{
				printf("Renderer could not be created!: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
				if (!loadMedia())
				{
					success = false;
				}
			}
		}

	
	}

	return success;
}

bool Game::loadMedia()
{
	bool success = true;
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize!: %s\n", IMG_GetError());
		success = false;
	}
	return success;
}

void Game::gameStart()
{
	isRunning = true;
	isOver = false;
	gameScore = 0;
	gameLevel = 1;
	board = new Board();
	block = new Block();
	nextBlock = new Block();
	nextText = new Text("asset\\FFFFORWA.TTF", "NEXT: " , 20, 255, 255, 255);
	nextDst.h = nextText->getHeight();
	nextDst.w = nextText->getWidth();
	nextDst.x = 3 * SCREEN_WIDTH / 4 - nextDst.w;
	nextDst.y = SCREEN_HEIGHT / 4;

	scoreText = new Text("asset\\FFFFORWA.TTF", "SCORE: ", 20, 255, 255, 255);
	scoreDst.h = scoreText->getHeight();
	scoreDst.w = scoreText->getWidth();
	scoreDst.x = 3 * SCREEN_WIDTH / 4 - scoreDst.w;
	scoreDst.y = SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 3;

	levelText = new Text("asset\\FFFFORWA.TTF", "LEVEL: ", 20, 255, 255, 255);
	levelDst.h = levelText->getHeight();
	levelDst.w = levelText->getWidth();
	levelDst.x = 3 * SCREEN_WIDTH / 4 - scoreDst.w;
	levelDst.y = SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 3 + levelDst.h;

	updateScore();
	updateLevel();

	board->init();
	block->init();
	nextBlock->init();
	
	fallStart = SDL_GetTicks();
	fallCount = 500;

	run();
}


void Game::run()
{
	while (isRunning)
	{
		if (isOver == true)
		{
			break;
		}
		frameStart = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
		
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_UP:
					switch (block->blockType)
					{
						case O: break; 
						case I: if (!checkRotateCollision(block)) board->rotateBlock(block); break;
						case S: if (!checkRotateCollision(block)) board->rotateBlock(block); break;
						case Z: if (!checkRotateCollision(block)) board->rotateBlock(block); break;
						case L: if (!checkRotateCollision(block)) board->rotateBlock(block); break;
						case J: if (!checkRotateCollision(block)) board->rotateBlock(block); break;
						case T: if (!checkRotateCollision(block)) board->rotateBlock(block); break;
					}
					break;
				case SDLK_LEFT:
					if(!checkMoveCollision(SDLK_LEFT))
						board->moveBlock(block, SDLK_LEFT);
					break;
				case SDLK_RIGHT:
					if (!checkMoveCollision(SDLK_RIGHT))
						board->moveBlock(block, SDLK_RIGHT);
					break;
				case SDLK_DOWN:
					if (checkCollision())
					{
						block->isActive = false;
						for (int i = 0; i < 4; i++)
						{
							board->landedMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos].tileType = BLOCK;
						}
					}
					else
					{
						block->fall();
						for (int i = 0; i < 4; i++)
						{
							board->tileMap[block->blockPiece[i].pos.ypos-1][block->blockPiece[i].pos.xpos].tileType = TILE::EMPTY;
						}
					}
					break;
				case SDLK_SPACE:
					while (1)
					{
						if (checkCollision())
						{
							block->isActive = false;
							for (int i = 0; i < 4; i++)
							{
								board->landedMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos].tileType = BLOCK;
							}
							break;
						}
						else
						{
							block->fall();
							for (int i = 0; i < 4; i++)
							{
								board->tileMap[block->blockPiece[i].pos.ypos - 1][block->blockPiece[i].pos.xpos].tileType = TILE::EMPTY;
							}
						}
					}
					break;
				default:
					break;
			}
		}
		else if(event.type == SDL_QUIT)
			isRunning = false;
	}
}

void Game::update()
{
	board->clearBlockOnMap(block);
	currentTime = SDL_GetTicks();
	if (currentTime - fallStart > fallCount)
	{
		if (checkCollision())
		{
			block->isActive = false;
			for (int i = 0; i < 4; i++)
			{
				board->landedMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos].tileType = BLOCK;
			}
		}
		else 
		{
			block->fall();
		}
		fallStart = SDL_GetTicks();
	}
	board->setBlockOnMap(block);
	if (board->checkLine(gameScore))
	{
		isOver = true;
	}
	updateScore();
	updateLevel();
	if (block->isActive == false)
	{
		delete block;
		block = nextBlock;
		nextBlock = new Block();
		nextBlock->init();
	}
}

void Game::updateScore()
{
	if (scoreNumberText != NULL)
	{
		scoreNumberText->destroy();
		scoreNumberText = NULL;
	}
	std::string str = std::to_string(gameScore);
	scoreNumberText = new Text("asset\\FFFFORWA.TTF", str, 20, 255, 255, 255);
	scoreNumberDst.h = scoreNumberText->getHeight();
	scoreNumberDst.w = scoreNumberText->getWidth();
	scoreNumberDst.x = 3 * SCREEN_WIDTH / 4 - scoreNumberDst.w + 9 *scoreNumberDst.w / 10;
	scoreNumberDst.y = SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 3;

	if (gameScore >= 10 && gameScore <= 900)
	{
		gameLevel = 1 + ((gameScore - 10) / 100);
	}
	else if (gameScore >= 910)
	{
		gameLevel = 10;
	}
	fallCount = (11 - gameLevel) * 50;
}

void Game::updateLevel()
{
	if (levelNumberText != NULL)
	{
		levelNumberText->destroy();
		levelNumberText = NULL;
	}
	std::string str = std::to_string(gameLevel);
	levelNumberText = new Text("asset\\FFFFORWA.TTF", str, 20, 255, 255, 255);
	levelNumberDst.h = levelNumberText->getHeight();
	levelNumberDst.w = levelNumberText->getWidth();
	levelNumberDst.x = 3 * SCREEN_WIDTH / 4 - levelNumberDst.w + 9 * levelNumberDst.w / 10;
	levelNumberDst.y = SCREEN_HEIGHT / 4 + SCREEN_HEIGHT / 3 + levelNumberDst.h;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	board->draw();
	board->drawBlockOnNext(nextBlock);
	nextText->render(&nextDst);
	scoreText->render(&scoreDst);
	scoreNumberText->render(&scoreNumberDst);
	levelText->render(&levelDst);
	levelNumberText->render(&levelNumberDst);
	SDL_RenderPresent(renderer);
}

void Game::gameOver()
{
	if (board != NULL) board->destroy();
	if (block != NULL) block->destroy();
	if (nextBlock != NULL) nextBlock->destroy();
	if (scoreText != NULL) scoreText->destroy();
	if (nextText != NULL) nextText->destroy();
	if (scoreNumberText != NULL) scoreNumberText->destroy();

	board = NULL;
	block = NULL;
	nextBlock = NULL;
	scoreText = NULL;
	nextText = NULL;
	scoreNumberText = NULL;
}

bool Game::checkCollision()
{
	bool crash = false;

	for (int i = 0; i < 4; i++)
	{
		if (board->landedMap[block->blockPiece[i].pos.ypos + 1][block->blockPiece[i].pos.xpos].tileType == BORDER ||
			board->landedMap[block->blockPiece[i].pos.ypos + 1][block->blockPiece[i].pos.xpos].tileType == BLOCK) 
			crash = true;
	}

	return crash;
}

bool Game::checkMoveCollision(int key)
{
	bool crash = false;

	switch (key)
	{
		case SDLK_LEFT:
			for (int i = 0; i < 4; i++)
			{
				if (board->landedMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos - 1].tileType == BORDER ||
					board->landedMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos - 1].tileType == BLOCK)
					crash = true;
			}
			break;
		case SDLK_RIGHT:
			for (int i = 0; i < 4; i++)
			{
				if (board->landedMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos + 1].tileType == BORDER ||
					board->landedMap[block->blockPiece[i].pos.ypos][block->blockPiece[i].pos.xpos + 1].tileType == BLOCK)
					crash = true;
			}
			break;
	}
	return crash;
}

bool Game::checkRotateCollision(Block * block)
{
	bool crash = false;
	Tile temp[4];
	switch (block->blockType)
	{
		case I:
			if (block->rotateType == 0)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos + 2;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos - 1;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos + 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos + 1;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos - 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos + 2;
			}
			else
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos - 2;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos + 1;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos - 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos - 1;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos + 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos - 2;

			}
			break;
		case S:
			if (block->rotateType == 0)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos + 1;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos - 2;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos - 1;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos + 1;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos + 1;
			}
			else
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos - 1;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos + 2;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos + 1;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos - 1;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos - 1;
			}
			break;
		case Z:
			if (block->rotateType == 0)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos + 2;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos - 1;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos + 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos - 1;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos - 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos;
			}
			else
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos - 2;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos + 1;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos - 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos + 1;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos + 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos;
			}
			break;
		case L:
			if (block->rotateType == 0)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos + 2;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos + 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos + 1;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos - 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos - 1;
			}
			else if (block->rotateType == 1)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos - 2;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos + 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos - 1;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos - 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos + 1;
			}
			else if (block->rotateType == 2)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos - 2;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos - 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos - 1;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos + 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos + 1;
			}
			else if (block->rotateType == 3)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos + 2;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos - 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos + 1;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos + 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos - 1;
			}
			break;
		case J:
			if (block->rotateType == 0)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos + 2;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos - 1;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos - 1;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos - 1;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos - 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos;
			}
			else if (block->rotateType == 1)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos - 2;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos - 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos + 1;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos + 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos - 1;
			}
			else if (block->rotateType == 2)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos + 1;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos + 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos + 1;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos - 2;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos + 1;
			}
			else if (block->rotateType == 3)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos - 1;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos + 1;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos + 1;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos - 1;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos + 2;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos;
			}
			break;
		case T:
			if (block->rotateType == 0)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos + 1;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos - 1;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos;
			}
			else if (block->rotateType == 1)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos - 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos - 1;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos + 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos - 1;
			}
			else if (block->rotateType == 2)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos - 1;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos + 1;
			}
			else if (block->rotateType == 3)
			{
				temp[0].pos.xpos = block->blockPiece[0].pos.xpos - 1;
				temp[0].pos.ypos = block->blockPiece[0].pos.ypos + 1;
				temp[1].pos.xpos = block->blockPiece[1].pos.xpos + 1;
				temp[1].pos.ypos = block->blockPiece[1].pos.ypos;
				temp[2].pos.xpos = block->blockPiece[2].pos.xpos + 1;
				temp[2].pos.ypos = block->blockPiece[2].pos.ypos;
				temp[3].pos.xpos = block->blockPiece[3].pos.xpos;
				temp[3].pos.ypos = block->blockPiece[3].pos.ypos;
			}
			break;
		default: break;
	}

	for (int i = 0; i < 4; i++)
	{
		if (board->landedMap[temp[i].pos.ypos][temp[i].pos.xpos].tileType == TILE::BLOCK ||
			board->landedMap[temp[i].pos.ypos][temp[i].pos.xpos].tileType == TILE::BORDER)
			crash = true;
	}
	return crash;
}

void Game::close()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	if(board != NULL) board->destroy();
	if(block != NULL) block->destroy();
	if(nextBlock != NULL) nextBlock->destroy();
	if (scoreText != NULL) scoreText->destroy();
	if (nextText != NULL) nextText->destroy();
	if (scoreNumberText != NULL) scoreNumberText->destroy();

	board = NULL;
	block = NULL;
	nextBlock = NULL;
	scoreText = NULL;
	nextText = NULL;
	scoreNumberText = NULL;

	SDL_Quit();
}

