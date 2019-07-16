#pragma once
#include "Navigator.h"
#include "CommonNavigation.h"

/**
 * @author David Wadsworth
 * 
 * In charge of screen transforming navigation
 */


namespace Navigation
{
	class DisplayPrompt final : public Delay
	{
		int prompt_id_;
		SDL_Rect* prompt_rect_;
		Assets::Prompt prompt_;
	public:
		DisplayPrompt(Manager * manager, Uint32 delay, int prompt_id);
		void init() override;
		void close() override;
	};

	class DisplayRoundPrompt final : public Delay
	{
		SDL_Rect *round_dest_, *tens_dest_, *ones_dest_;
		int round_id_, number_id_, round_number_;
		Assets::Prompt round_, tens_, ones_;
	public:
		DisplayRoundPrompt(Manager * manager, Uint32 delay, int round_id, int number_id, int round_number);
		void init() override;
		void close() override;
	};

	class BackgroundTransition final : public Navigator
	{
		int frames_, texture_id_;
		Assets::Transition transition_;
	public:
		BackgroundTransition(Manager * manager, int texture_id, int frames);
		void init() override;
		int choose_path() override;
		void close() override;
	};
}
