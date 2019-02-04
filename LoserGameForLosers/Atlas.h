#pragma once
#include <string>
#include <utility>
#include <vector>

struct SpriteAddress
{
	SpriteAddress(std::string id) 
		: id(id)
	{}
	std::string id;
	SDL_Rect src;
	int x_offset, y_offset, original_width, original_height, rotation;
};

struct Atlas
{
	std::string path;
	int width, height;
	std::vector<SpriteAddress *> addresses;

	Atlas(std::string path, int width, int height)
		: path(path), width(width), height(height)
	{}

	void add_address(std::string id, int x, int y, int w, int h)
	{
		auto address = new SpriteAddress(id);
		address->src.x = x;
		address->src.y = y;
		address->src.w = w;
		address->src.h = h;
		address->x_offset = 0;
		address->y_offset = 0;
		address->original_width = w;
		address->original_height = h;
		address->rotation = 0;

		addresses.push_back(address);
		current_address_ = address;
	}

	void add_trim(int ox, int oy, int ow, int oh)
	{
		current_address_->x_offset = ox;
		current_address_->y_offset = oy;
		current_address_->original_width = ow;
		current_address_->original_height = oh;
	}

	void is_rotated()
	{
		current_address_->rotation = 90;
	}
private:
	SpriteAddress * current_address_;
};