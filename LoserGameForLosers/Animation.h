#pragma once
#include "SDL.h"

struct Animation
{
	int index;
	int frames;
	int speed;
	int rotations;
	std::vector<int> call_ids;
	SDL_RendererFlip flip;

	Animation(): index(0), frames(0), speed(0), rotations(0), flip(SDL_FLIP_NONE)
	{}

	Animation(const int index, const int frames, const int speed)
		: index(index), frames(frames), speed(speed)
	{}

	Animation(const int index, const int frames, const int speed, const int rots, const SDL_RendererFlip flp)
		: index(index), frames(frames), speed(speed), rotations(rots), flip(flp)
	{}

};