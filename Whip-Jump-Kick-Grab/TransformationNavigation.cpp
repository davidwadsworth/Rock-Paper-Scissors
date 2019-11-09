#include "stdafx.h"
#include "TransformationNavigation.h"

namespace Navigation
{
	DisplayPrompt::DisplayPrompt(Manager * manager, const Uint32 delay, const int prompt_id)
		: Delay(delay), prompt_id_(prompt_id), prompt_rect_(new SDL_Rect{0, 90, SCREEN_WIDTH, 160}), prompt_(manager)
	{
	}

	void DisplayPrompt::init()
	{
		prompt_.create(prompt_id_, prompt_rect_);
	}

	void DisplayPrompt::close()
	{
		prompt_.destroy();
	}


	DisplayRoundPrompt::DisplayRoundPrompt(Manager * manager, const Uint32 delay, const int round_id, const int number_id, const int round_number)
		: Delay(delay), round_dest_(new SDL_Rect{ 0,90, 600, 160 }), tens_dest_(new SDL_Rect{ 600, 90, 100, 160 }), ones_dest_(new SDL_Rect{ 700, 90, 100, 160 }),
		round_id_(round_id), number_id_(number_id), round_number_(round_number), round_(manager), tens_(manager), ones_(manager)
	{}

	void DisplayRoundPrompt::init()
	{
		round_.create(round_id_, round_dest_);
		tens_.create(number_id_ + round_number_ / 10, tens_dest_);
		ones_.create(number_id_ + round_number_ % 10, ones_dest_);
	}

	void DisplayRoundPrompt::close()
	{
		round_.destroy();
		tens_.destroy();
		ones_.destroy();
	}


	BackgroundTransition::BackgroundTransition(Manager * manager, const int texture_id, const int frames)
		: frames_(frames), texture_id_(texture_id), transition_(manager)
	{}

	void BackgroundTransition::init()
	{
		transition_.create(frames_, texture_id_);
	}

	int BackgroundTransition::choose_path()
	{
		return transition_.get_asset()->get_component<FadeComponent>().cycles_completed();
	}

	void BackgroundTransition::close()
	{
		transition_.destroy();
	}

}


