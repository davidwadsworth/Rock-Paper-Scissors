#pragma once
#include "DataCollection.h"
#include <vector>

/**
 * @author David Wadsworth
 */

struct AtlasData
{
	int texture_id = NULL;
	std::string n;
	int x = NULL;
	int y = NULL;
	int w = NULL;
	int h = NULL;
	int offset_x = 0;
	int offset_y = 0;
	int original_w = NULL;
	int original_h = NULL;
	bool is_rotated = false;
};

struct AtlasCollection : DataCollection 
{
	int texture_id = NULL;
	int image_width = NULL;
	int image_height = NULL;
	std::vector<AtlasData> data{};
};
