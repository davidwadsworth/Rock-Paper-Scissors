#pragma once
#include "Navigator.h"
#include "Timer.h"
#include "GameState.h"

namespace Navigation
{
	class Delay : public Navigator
	{
		Uint32 total_delay_, ticks_;
		Timer *timer_;
	public:
		explicit Delay(Uint32 delay);
		int choose_path() override;
	};

	class ChangeController final : public Navigator
	{
		Entity * player_;
		CONTROLLER_DATA new_controller_;
	public:

		ChangeController(Entity * player, CONTROLLER_DATA new_controller);

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
		Entity *target_, *option_box_;
		int input_id_, options_id_;
		Vector2D position_;
	public:
		CreateOptionBox(int options_id, int input_id, Vector2D position);
		CreateOptionBox(int options_id, int input_id, Vector2D position, Entity* target);

		void init() override;
		int choose_path() override;
		void close() override;
	};
}



