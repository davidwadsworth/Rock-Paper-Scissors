#pragma once
#include "DataCollection.h"
#include <vector>

struct AtlasData
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

struct AtlasCollection : DataCollection 
{
	int texture_id;
	int image_width;
	int image_height;
	std::vector<AtlasData> data;
};
