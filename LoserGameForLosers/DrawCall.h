#pragma once
#include "SDL.h"
#include "AtlasData.h"

class DrawCall
{
	SpriteData * data_;
	SDL_Point rotation_axis_, rotation_;
	bool is_rotated_;
	int original_w_, original_h_;
	int data_w_, data_h_;
	Vector2D data_offset_, other_offset_;
	void find_rotation_point();
	void init();
public:
	int height, width;
	
	DrawCall() = default;
	DrawCall(int texture_id, SDL_Rect src, SDL_Rect *dest, SDL_RendererFlip flip, int rotation, SDL_Point * point);
	DrawCall(SpriteData * data, SDL_Rect* dest, SDL_RendererFlip flip, int rotation);
	void update_rotation_point(float scaling) const;
	void update_height(int h);
	void update_width(int w);
	Vector2D position_offset();

	SDL_Point* rotation_point;
	int rotation = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Texture * tex;
	SDL_Rect src, *dest;

};
