#pragma once
#include "ECS.h"
#include "Link.h"
#include <map>

class OptionsComponent: public Component
{
	int y_pos_;
	int x_pos_;
	
public:
	Options * current_options;

	OptionsComponent()
	{}

	explicit OptionsComponent(Options* choices)
		: current_options(choices)
	{}

	void init() override
	{
		y_pos_ = 0;
		x_pos_ = 0;
	}

	void load_new_options(Options* choices)
	 {
		current_options = choices;
	 }

	void next_x(const int x_inc)
	{
		x_pos_ += x_inc;
		if (x_pos_ < 0)
			x_pos_ = current_options->choices.size() - 1;
		if (x_pos_ > current_options->choices.size() - 1)
			x_pos_ = 0;
	}

	void next_y(const int y_inc)
	{
		y_pos_ += y_inc;
		if (y_pos_ < 0)
			y_pos_ = current_options->choices[x_pos_].size() - 1;
		if (y_pos_ > current_options->choices[x_pos_].size() - 1)
			y_pos_ = 0;
	}

	Link * get_current_link() const
	{
		return current_options->choices[x_pos_][y_pos_];
	}
	
};