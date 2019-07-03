#pragma once
#include "Game.h"
#include "Link.h"
#include "CommonLinkCommands.h"
#include "BitmapFont.h"


class CursorLeftLink : public Link
{
public:
	explicit CursorLeftLink(BitmapFont* font, const int padding, Vector2D alignment, std::string asset, Command* command)
		: font_(font), padding_(padding), alignment_(alignment), text_(asset), command_(command)
	{}

	~CursorLeftLink()
	{}

	void set_link_information(SDL_Rect * starting_rect) override;

	void set_position(int x, int y) override 
	{
		pos_.x = x;
		pos_.y = y;
	}

	Command * get_command() override { return command_; }
	std::string get_text() override { return text_; }
	SDL_Rect* get_link_dimensions() override { return link_dimensions_; }
	SDL_Rect* get_box_dimensions() override { return box_dimensions_; }
	SDL_Rect* get_cursor_dimensions() override { return cursor_dimensions_; }


private:
	BitmapFont * font_;
	SDL_Point pos_;
	Command * command_;
	int padding_;
	Vector2D alignment_;
	std::string text_;
	SDL_Rect* link_dimensions_{};
	SDL_Rect* box_dimensions_{};
	SDL_Rect* cursor_dimensions_{};
};
