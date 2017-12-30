#pragma once
#include <SDL_image.h>
#include <SDL.h>

enum COLOR
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	PINK,
	ORANGE,
};

enum TYPE
{
	// http://www.colinfahey.com/tetris/tetris_diagram_pieces_orientations_new.jpg
	O,
	I,
	S,
	Z,
	L,
	J,
	T,
};

class Block
{
	private:
	int color;
	SDL_Texture* blockTexture;
	bool isActive;

	public:
	int orientX;
	int orientY;

	void init();
	void update();
	void render(SDL_Rect src, SDL_Rect dst);
};