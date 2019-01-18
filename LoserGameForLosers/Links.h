#pragma once
#include "Game.h"
#include "Link.h"
#include "LinkCommands.h"


class CursorLeftLink : public Link
{
public:
	explicit CursorLeftLink(const int padding, Vector2D alignment, std::string asset, Command* command, std::string font)
		: padding_(padding), alignment_(alignment), text_(asset), command_(command), font_(font)
	{}

	~CursorLeftLink()
	{}

	void set_link_information(SDL_Rect * starting_rect) override
	{
		auto bitmap_font = Game::assets->get_bitmap_font();

		link_dimensions_ = &bitmap_font->text_dimensions(static_cast<int>(pos_.x) + CURSOR_WIDTH + 4 * padding_, static_cast<int>(pos_.y) + 2 * padding_, text_);

		if (link_dimensions_->h < CURSOR_HEIGHT)
			link_dimensions_->h = CURSOR_HEIGHT;

		int x_offset = 0;
		int y_offset = 0;

		if (starting_rect)
		{
			x_offset = (link_dimensions_->w + CURSOR_WIDTH + padding_ * 6 + pos_.x - (starting_rect->w + starting_rect->x)) * alignment_.x;
			y_offset = (link_dimensions_->h + padding_ * 4 + pos_.y - (starting_rect->h + starting_rect->y)) * alignment_.y;
		}

		link_dimensions_->x -= x_offset;
		link_dimensions_->y -= y_offset;
		cursor_dimensions_ = new SDL_Rect{ static_cast<int>(pos_.x) + 2 * padding_ - x_offset, static_cast<int>(pos_.y) + (link_dimensions_->h) / 2 - y_offset, CURSOR_WIDTH, CURSOR_WIDTH };
		box_dimensions_ = new SDL_Rect{ static_cast<int>(pos_.x) - x_offset, static_cast<int>(pos_.y) - y_offset, link_dimensions_->w + cursor_dimensions_->w + padding_ * 6, link_dimensions_->h + padding_ * 4 };
	}

	void set_position(Vector2D position) override { }

	Command * get_command() override { return command_; }
	std::string get_text() override { return text_; }
	SDL_Rect* get_link_dimensions() override { return link_dimensions_; }
	SDL_Rect* get_box_dimensions() override { return box_dimensions_; }
	SDL_Rect* get_cursor_dimensions() override { return cursor_dimensions_; }


private:
	Vector2D pos_;
	Command * command_;
	int padding_;
	Vector2D alignment_;
	std::string text_, font_;
	SDL_Rect* link_dimensions_{};
	SDL_Rect* box_dimensions_{};
	SDL_Rect* cursor_dimensions_{};
};