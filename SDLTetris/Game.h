#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
class Board;
class Block;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 768;

class Game
{
	private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Texture* boardTexture;

	SDL_Thread* updateThread;

	bool isRunning = false;
	Block* block;

	public:
	
	static SDL_Renderer* renderer;
	Board* board;
	
	bool running() { return isRunning; }
	bool init();
	bool loadMedia();
	void run();
	void handleEvents();
	void update();
	void render();
	bool checkCollision();
	bool checkMoveCollision(int key);
	void close();
	

};
#endif /*GAME_H */
