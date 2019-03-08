#include "stdafx.h"
#include "DrawCall.h"

void DrawCall::init()
{
	tex = Game::assets->get_texture(atlas_texture_sheet_main);

	src.x = data_->x;
	src.y = data_->y;
	src.w = data_->w;
	src.h = data_->h;

	dest->x = data_offset_.x;
	dest->y = data_offset_.y;
	dest->w = src.w;
	dest->h = src.h;

	rotation_point = { static_cast<int>(rotation_axis_ / 2), static_cast<int>(rotation_axis_ / 2) };

	if (is_rotated_)
	{
		rotation -= 90;
	}
}

void DrawCall::update_call(Vector2D* position, Vector2D* scaling)
{
	dest->x = static_cast<int>(position->x + data_offset_.x * scaling->x);
	dest->y = static_cast<int>(position->y + data_offset_.y * scaling->y);
	dest->w = static_cast<int>(src.w * scaling->x);
	dest->h = static_cast<int>(src.h * scaling->y);
	if (is_rotated_)
		rotation_point = { static_cast<int>(rotation_axis_ * scaling->y / 2), static_cast<int>(rotation_axis_ * scaling->x / 2) };

}