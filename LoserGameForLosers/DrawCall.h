#pragma once
#include "SDL.h"
#include "AtlasData.h"

class DrawCall
{
	SpriteData data_;
	bool is_rotated_;
	SDL_Point data_offset_;
	int rotation_axis_;
public:

	DrawCall() = default;

	explicit DrawCall(const SpriteData data, SDL_Rect* dest, const int rotation = 0, const SDL_RendererFlip flip = SDL_FLIP_NONE)
		: data_(data), is_rotated_(data.is_rotated), rotation(rotation), flip(flip), dest(dest)
	{
		data_offset_.x = data_.offset_x;
		data_offset_.y = 0;

		if (!is_rotated_)
			data_offset_.y = data_.offset_y;

		rotation_axis_ = data_.original_h;

		if (this->flip == SDL_FLIP_HORIZONTAL)
		{
			data_offset_.x = data_.offset_x;
			data_offset_.y = data_.offset_y;

			if (!is_rotated_)
			{
				data_offset_.x += data_.original_w - data_.w;
			}
			else
			{
				this->rotation += 180;
			}
		}

		init();
	}

	void init();

	void update_call(Vector2D* position, Vector2D* scaling);

	SDL_Point rotation_point;
	int rotation = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	int id;
	SDL_Texture * tex;
	SDL_Rect src, *dest;

};
