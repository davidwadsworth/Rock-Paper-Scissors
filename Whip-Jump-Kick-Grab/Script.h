#pragma once
#include "NavigationPreset.h"

/**
 * @author David Wadsworth
 *
 * Unique pathway declarations
*/

class CircularScript : public Path
{
	int current_pos_ = 0;
	std::vector<NavigationPreset*> presets_;
public:
	virtual ~CircularScript() 
	{
		CircularScript::close();
	}

	void add_preset(NavigationPreset * preset)
	{
		if (!get_head())
		{
			preset->init();
			set_head(preset->get_trunk());
			get_head()->current->init();
		}

		presets_.push_back(preset);
	}

	void navigate_path() override
	{
		if (!get_head())
			return;

		if (get_head()->has_current())
			get_head()->current->navigate_path();
		else
		{
			if (get_head()->next)
			{
				set_head(get_head()->next);
				get_head()->current->init();
				return;
			}

			if (++current_pos_ > presets_.size() - 1)
				current_pos_ = 0;

			presets_[current_pos_]->init();
			set_head(presets_[current_pos_]->get_trunk());
			get_head()->current->init();
		}
	}
	
	virtual void close()
	{
		for (auto p : presets_)
			p->close();
	}
};

class AIScript : public Path
{

public:
	AIScript() = default;

	void navigate_path() override
	{
		if (!get_head())
			return;

		if (get_head()->has_current())
			get_head()->current->navigate_path();
		else
			get_head()->reset();
	}

};