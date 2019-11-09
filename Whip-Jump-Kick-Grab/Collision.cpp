#include "stdafx.h"
#include "Collision.h"

bool Collision::aabb(const SDL_Rect& rec_a, const SDL_Rect& rec_b)
{
	return rec_a.x + rec_a.w >= rec_b.x && rec_b.x + rec_b.w >= rec_a.x && rec_a.y + rec_a.h >= rec_b.y && rec_b.y + rec_b.h >= rec_a.y;
}

bool Collision::aabb(const int x_1, const int y_1, const int w_1, const int h_1, const int x_2, const int y_2, const int w_2, const int h_2)
{
	return x_1 + w_1 >= x_2 && x_2 + w_2 >= x_1 && y_1 + h_1 >= y_2 && y_2 + h_2 >= y_1;
}

bool Collision::aabb(const SDL_Rect & rec_a, const SDL_Rect & rec_b, const int padding)
{
	return rec_a.x + rec_a.w - padding >= rec_b.x && rec_b.x + rec_b.w + padding >= rec_a.x && rec_a.y + rec_a.h - padding >= rec_b.y && rec_b.y + rec_b.h + padding >= rec_a.y;
}
