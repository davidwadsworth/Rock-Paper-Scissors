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
	int x, y, width, height, x_offset, y_offset, original_width, original_height, rotation;
};

struct Atlas
{
	const char * path;
	int width, height;
	std::vector<SpriteAddress *> adresses;

	Atlas(const char * path, int width, int height)
		: path(path), width(width), height(height)
	{}

	void add_address(std::string id, int x, int y, int w, int h)
	{
		auto address = new SpriteAddress(id);
		address->x = x;
		address->y = y;
		address->width = w;
		address->height = h;
		address->x_offset = 0;
		address->y_offset = 0;
		address->original_width = w;
		address->original_height = h;
		address->rotation = 0;

		adresses.push_back(address);
		current_address_ = address;
	}

	void add_trim(int ox, int oy, int ow, int oh)
	{
		current_address_->x_offset = ox;
		current_address_->y_offset = oy;
		current_address_->original_width = ow;
		current_address_->original_height = oh;
	}

	void add_rotation(int r)
	{
		current_address_->rotation = r;
	}
private:
	SpriteAddress * current_address_;
};