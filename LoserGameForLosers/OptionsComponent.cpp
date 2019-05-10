#include "stdafx.h"

OptionsComponent::OptionsComponent(const int options_id, const int x, const int y, const Vector2D align, const int pad)
	: y_pos_(0), x_pos_(0), padding_(pad), alignment_(align), data_(Game::data->get_options_data(options_id)), target_(nullptr), position{ x, y }
{}

void OptionsComponent::init()
{
	options_ = Options(data_);
	current_links = options_.build_options(position.x, position.y, alignment_, padding_);
	box = options_.box;
}

void OptionsComponent::change_target(Entity * target)
{
	target_ = target;
	for (auto x : current_links)
	{
		for (auto y : x)
		{
			auto y_target = dynamic_cast<Targetable*>(y->get_command());

			if (y_target)
				y_target->change_target(target_);
		}
	}
}

void OptionsComponent::next_x(const int x_inc)
{
	x_pos_ += x_inc;
	if (x_pos_ < 0)
		x_pos_ = current_links.size() - 1;
	if (x_pos_ > current_links.size() - 1)
		x_pos_ = 0;
}

void OptionsComponent::next_y(const int y_inc)
{
	y_pos_ += y_inc;
	if (y_pos_ < 0)
		y_pos_ = current_links[x_pos_].size() - 1;
	if (y_pos_ > current_links[x_pos_].size() - 1)
		y_pos_ = 0;
}

int OptionsComponent::get_path() const
{
	return selection_made_ ? data_->data[x_pos_][y_pos_].path : 0;
}

Link * OptionsComponent::get_current_link()
{
	return current_links[x_pos_][y_pos_];
}

void OptionsComponent::make_selection()
{
	selection_made_ = true;
	get_current_link()->get_command()->execute(entity);
}
