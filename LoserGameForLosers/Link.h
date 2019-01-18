#pragma once
#include "Game.h"
#include "Options.h"


class Link
{
public:
	virtual ~Link() {}
	virtual void set_link_information(SDL_Rect * starting_rect = nullptr) = 0;
	virtual void set_position(Vector2D position) = 0;

	virtual Command* get_command() = 0;
	virtual std::string get_text() = 0;
	virtual SDL_Rect* get_link_dimensions() = 0;
	virtual SDL_Rect* get_box_dimensions() = 0;
	virtual SDL_Rect* get_cursor_dimensions() = 0;
};

