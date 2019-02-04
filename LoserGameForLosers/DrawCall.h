#pragma once
#include "SDL.h"
#include "Atlas.h"

struct DrawCall
{
public:
	int id;
	SDL_Texture * tex;
	SDL_Rect *src, *dest;
	SDL_Point * rotation_point;
	int rotation = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};
