#pragma once
#include "Link.h"
#include "LinkBuilder.h"
#include "OptionsData.h"

/**
 * @author David Wadsworth
 * 
 * In charge of building option boxes from scratch
 */

class Options
{
	OptionsData * data_;
	BitmapFont * font_;
public:
	std::string id;
	SDL_Rect box;
	std::vector<std::vector<Link *>> links{};

	Options()
		: data_(nullptr), font_(nullptr), box()
	{}

	explicit Options(OptionsData* data, BitmapFont* font)
		: data_(data), font_(font), box()
	{}

	std::vector<std::vector<Link *>> build_options(int start_x, int start_y, Vector2D alignment, const int padding);
};

