#pragma once

struct SpriteData
{
	int texture_id;
	std::string n;
	int x;
	int y;
	int w;
	int h;
	int offset_x = 0;
	int offset_y = 0;
	int original_w;
	int original_h;
	bool is_rotated = false;
};

struct AtlasData
{
	std::string image_path;
	int texture_id;
	int image_width;
	int image_height;
	std::vector<SpriteData> data;
};