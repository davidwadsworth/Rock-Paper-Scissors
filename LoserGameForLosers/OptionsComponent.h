#pragma once
#include "ECS.h"
#include "Link.h"
#include "Options.h"
#include "PlayerComponent.h"

class OptionsComponent : public Component
{
	int y_pos_, x_pos_, padding_;
	Vector2D alignment_;

	Options options_;
	Entity * target_;
public:
	SDL_Rect box;
	std::vector<std::vector<Link*>> current_links;
	int options_id;
	SDL_Point position;

	explicit OptionsComponent(const int options_id, const int x, const int y, const Vector2D align, const int pad)
		: padding_(pad), options_id(options_id), alignment_(align), position{x, y}
	{
	}

	void init() override
	{
		options_ = Options(Game::data->get_options_data(this->options_id));
		current_links = options_.build_options(position.x, position.y, alignment_, padding_);
		x_pos_ = 0;
		y_pos_ = 0;
		box = options_.box;
	}

	void change_target(Entity * target)
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

	void change_options(const int new_options);


	void next_x(const int x_inc)
	{
		x_pos_ += x_inc;
		if (x_pos_ < 0)
			x_pos_ = current_links.size() - 1;
		if (x_pos_ > current_links.size() - 1)
			x_pos_ = 0;
	}

	void next_y(const int y_inc)
	{
		y_pos_ += y_inc;
		if (y_pos_ < 0)
			y_pos_ = current_links[x_pos_].size() - 1;
		if (y_pos_ > current_links[x_pos_].size() - 1)
			y_pos_ = 0;
	}

	Link * get_current_link() const
	{
		return current_links[x_pos_][y_pos_];
	}
	
};
