#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Menu;
class Board;
class Block;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;

class Game
{
	private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	Menu* menu;

	bool isOver = false;
	Block* block;
	Block* nextBlock;

	public:
	
	static SDL_Renderer* renderer;
	Board* board;
	bool isRunning = true;

	bool init();
	bool loadMedia();
	void gameStart();
	void run();
	void handleEvents();
	void update();
	void render();
	void gameOver();
	bool checkCollision();
	bool checkMoveCollision(int key);
	bool checkRotateCollision(Block* block);
	void close();
	

};
#endif /*GAME_H */
