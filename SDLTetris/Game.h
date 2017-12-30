#ifndef GAME_H
#define GAME_H
#include <SDL.h>

class Game
{
	private:
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	SDL_Texture* boardTexture;
	bool isRunning = false;

	public:
	Game();
	~Game();

	static SDL_Renderer* renderer;
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
