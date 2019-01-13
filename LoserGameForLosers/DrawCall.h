#pragma once
#include "SDL.h"

struct DrawCall
{
public:
	DrawCall(SpriteAddress* sprite, SDL_Rect* dest, int rotation, SDL_RendererFlip flip)
		: sprite_address(sprite), dest(dest), rotation(rotation), flip(flip)
	{}
	~DrawCall() {}

	SpriteAddress* sprite_address;
	SDL_Rect *dest;
	int rotation;
	SDL_RendererFlip flip;
};
