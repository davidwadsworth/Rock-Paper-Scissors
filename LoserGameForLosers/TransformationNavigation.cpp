#include "stdafx.h"
#include "TransformationNavigation.h"

namespace Navigation
{
	DisplayPrompt::DisplayPrompt(const Uint32 delay, const int prompt_id)
		: Delay(delay), prompt_id_(prompt_id), prompt_rect_(new SDL_Rect{0, 0, SCREEN_WIDTH, 160}), prompt_(nullptr)
	{
	}

	void DisplayPrompt::init()
	{
		prompt_ = Game::assets->create_prompt(prompt_id_, prompt_rect_);
	}

	void DisplayPrompt::close()
	{
		prompt_->del_group(Game::group_prompts);
		prompt_->destroy();
	}


	DisplayRoundPrompt::DisplayRoundPrompt(const Uint32 delay, const int round_id, const int number_id, const int round_number)
		: Delay(delay), round_dest_(new SDL_Rect{ 0,0, 600, 160 }), tens_dest_(new SDL_Rect{ 600, 0, 100, 160 }), ones_dest_(new SDL_Rect{ 700, 0, 100, 160 }),
		round_id_(round_id), number_id_(number_id), round_number_(round_number),  round_prompt_(nullptr), tens_prompt_(nullptr), ones_prompt_(nullptr)
	{}

	void DisplayRoundPrompt::init()
	{
		round_prompt_ = Game::assets->create_prompt(round_id_, round_dest_);
		tens_prompt_ = Game::assets->create_prompt(number_id_ + round_number_ / 10, tens_dest_);
		ones_prompt_ = Game::assets->create_prompt(number_id_ + round_number_ % 10, ones_dest_);
	}

	void DisplayRoundPrompt::close()
	{
		round_prompt_->del_group(Game::group_prompts);
		round_prompt_->destroy();
		tens_prompt_->del_group(Game::group_prompts);
		tens_prompt_->destroy();
		ones_prompt_->del_group(Game::group_prompts);
		ones_prompt_->destroy();
	}


	BackgroundTransition::BackgroundTransition(const int frames)
		: frames_(frames), wipe_(nullptr)
	{}

	void BackgroundTransition::init()
	{
		wipe_ = Game::assets->create_background_transition(frames_);
		wipe_->add_group(Game::group_wipes);
	}

	int BackgroundTransition::choose_path()
	{
		return wipe_->get_component<FadeComponent>().cycles_completed();
	}

	void BackgroundTransition::close()
	{
		wipe_->destroy();
		wipe_->del_group(Game::group_wipes);
	}

}


