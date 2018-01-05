#ifndef BLOCK_H
#define BLOCK_H
#include <SDL.h>
#include "Tile.h"
enum TYPE
{
	// http://www.colinfahey.com/tetris/tetris_diagram_pieces_orientations_new.jpg
	O, // RED
	I, // ORANGE
	S, // YELLOW
	Z, // GREEN
	L, // BLUE
	J, // PINK
	T, // PURPLE
};

class Block
{
	private:
	int color;

	public:
	Block();
	int blockType;
	int rotateType;

	int getColor() { return color; };
	bool isActive;
	Tile blockPiece[4];
	void init();
	void fall();
	void rotate();
	void destroy();
};
#endif /* BLOCK_H */