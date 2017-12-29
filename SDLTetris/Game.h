#ifndef GAME_H
#define GAME_H
#include <SDL.h>

class Game
{
	private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	bool isRunning = false;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	public:
	Game();
	~Game();

	bool running() { return isRunning; }
	bool init();
	void run();
	void handleEvents();
	void update();
	void render();
	void close();
};
#endif /*GAME_H */
