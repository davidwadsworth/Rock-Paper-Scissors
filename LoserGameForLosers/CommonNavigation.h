#pragma once
#include "Navigator.h"
#include "Timer.h"
#include "GameState.h"

namespace Navigation
{
	class Delay : public Navigator
	{
		Uint32 total_delay_;
		Timer * timer_;
	public:
		explicit Delay(Uint32 delay);
		int choose_path() override;
	};

	class EnableController final : public Navigator
	{
		Entity * player_;
	public:
		explicit EnableController(Entity* player);
		int choose_path() override;
	};

	class DisableController final : public Navigator
	{
		Entity * player_;
	public:
		explicit DisableController(Entity* player);
		int choose_path() override;
	};

	class ChangeState final : public Navigator
	{
		game_states new_state_;
	public:
		explicit ChangeState(game_states new_state);

		int choose_path() override;
	};

	class CreateOptionBox : public Navigator
	{
		Entity *target_;
		int input_id_, options_id_, cursor_id_, glyph_id_, controller_id_;
		Vector2D position_;
		Assets::OptionBox option_box_;
	public:
		CreateOptionBox(Manager* manager, int glyph_id, int cursor_id, int options_id, int input_id, int controller_id, Vector2D position);
		CreateOptionBox(Manager* manager, int glyph_id, int cursor_id, int options_id, int input_id, int controller_id, Vector2D position, Entity* target);

		void init() override;
		int choose_path() override;
		void close() override;
	};
}



