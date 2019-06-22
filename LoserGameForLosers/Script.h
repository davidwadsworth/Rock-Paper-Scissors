#pragma once
#include "NavigationPreset.h"

class Script : public Path
{
	PathTrunk * head_ = nullptr;
	int current_pos_ = 0;
	std::vector<NavigationPreset*> presets_;
public:
	virtual ~Script() 
	{
		Script::close();
	}

	void add_preset(NavigationPreset * preset)
	{
		if (!head_)
		{
			preset->init();
			head_ = preset->get_trunk();
			head_->current->init();
		}

		presets_.push_back(preset);
	}

	void navigate_path() override
	{
		if (!head_)
			return;

		if (head_->has_current())
			head_->current->navigate_path();
		else
		{
			if (head_->next)
			{
				head_ = head_->next;
				head_->current->init();
				return;
			}

			if (++current_pos_ > presets_.size() - 1)
				current_pos_ = 0;

			presets_[current_pos_]->init();
			head_ = presets_[current_pos_]->get_trunk();
			head_->current->init();
		}
	}
	
	virtual void close()
	{
		for (auto p : presets_)
			p->close();
	}
};
