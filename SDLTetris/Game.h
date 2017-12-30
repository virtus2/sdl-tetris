#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>

class Board;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

class Game
{
	private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Texture* boardTexture;
	bool isRunning = false;

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
	void close();

};
#endif /*GAME_H */
