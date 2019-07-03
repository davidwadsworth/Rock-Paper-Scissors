#pragma once
#include "Link.h"
#include "LinkBuilder.h"
#include "OptionsData.h"

class Options
{
	OptionsData * data_;
	BitmapFont * font_;
public:
	std::string id;
	SDL_Rect box;
	std::vector<std::vector<Link *>> links{};

	Options() = default;

	explicit Options(OptionsData* data, BitmapFont* font)
		: data_(data), font_(font), box()
	{}

	std::vector<std::vector<Link *>> build_options(const int x, const int y, Vector2D alignment, const int padding);
	


	
};

