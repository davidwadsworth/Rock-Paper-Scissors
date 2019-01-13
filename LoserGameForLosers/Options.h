#pragma once
#include "Command.h"


struct Options
{
	Options()
	{}

	Options(const char * id)
		: id(id)
	{}

	std::string id;
	SDL_Rect box;
	std::vector<std::vector<Link *>> choices{};
};