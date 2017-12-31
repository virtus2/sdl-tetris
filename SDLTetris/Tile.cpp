#include "Tile.h"
#include <SDL.h>
#include "Game.h"
#include "TextureLoader.h"

void Tile::render(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst)
{
	SDL_RenderCopy(Game::renderer, texture, src, dst);
}
