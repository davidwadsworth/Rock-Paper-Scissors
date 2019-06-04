#pragma once
#include "Navigator.h"
#include "CommonNavigation.h"

namespace Navigation
{
	class DisplayPrompt final : public Delay
	{
		int prompt_id_;
		SDL_Rect* prompt_rect_;
		Entity* prompt_;
		AssetManager * asset_manager_;
	public:
		DisplayPrompt(AssetManager * asset_manager, Uint32 delay, int prompt_id);
		void init() override;
		void close() override;
	};

	class DisplayRoundPrompt final : public Delay
	{
		SDL_Rect *round_dest_, *tens_dest_, *ones_dest_;
		int round_id_, number_id_, round_number_;
		Entity * round_prompt_, *tens_prompt_, *ones_prompt_;
		AssetManager * asset_manager_;
	public:
		DisplayRoundPrompt(AssetManager * asset_manager, Uint32 delay, int round_id, int number_id, int round_number);
		void init() override;
		void close() override;
	};

	class BackgroundTransition final : public Navigator
	{
		int frames_;
		Entity* wipe_;
		AssetManager * asset_manager_;
	public:
		BackgroundTransition(AssetManager * asset_manager, int frames);
		void init() override;
		int choose_path() override;
		void close() override;
	};
}
