#pragma once
#include "SDL.h"
#include "AtlasData.h"

/**
 * @author David Wadsworth
 * 
 * In charge of decoding instructions from atlas sheet and making necessary edits before passing the information to be displayed on screen
 * as well as keeping track of non-atlas images
 */

class DrawCall
{
	AtlasData * data_;
	SDL_Point rotation_axis_;
	bool is_rotated_;
	int original_w_, original_h_;
	int data_w_, data_h_;
	Vector2D data_offset_, other_offset_;
	void find_rotation_point();
	void init();
public:
	int height, width, or_width, or_height;
	
	DrawCall();
	DrawCall(AtlasData * data, SDL_Rect* dest, SDL_RendererFlip flip, int rotation);
	DrawCall(SDL_Rect* src, SDL_Rect *dest, SDL_RendererFlip flip, int rotation, SDL_Point * point);
	void update_rotation_point(double scaling) const;
	void update_height(int h);
	void update_width(int w);
	Vector2D position_offset();

	SDL_Point* rotation_point;
	int rotation = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect *src, *dest;

};
