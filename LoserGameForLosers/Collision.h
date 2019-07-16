#pragma once

#include "SDL.h"

/**
 * @author Let's Make Games
 * @author David Wadsworth
 * AABB collision
 */

class Collision{
public:
	static bool aabb(const SDL_Rect& rec_a, const SDL_Rect& rec_b);
	static bool aabb(int x_1, int y_1, int w_1, int h_1, int x_2, int y_2, int w_2, int h_2);
	static bool aabb(const SDL_Rect& rec_a, const SDL_Rect& rec_b, int padding);
};