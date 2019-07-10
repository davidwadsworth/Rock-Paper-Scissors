#pragma once
#include "ECS.h"
#include "Constants.h"
#include "InputCommand.h"

/**
 * Commands that are bound to keys
 */


namespace InputCommands
{
	class Move : public InputCommand
	{
	public:
		Move(std::string move_info)
		{
			std::string v_sc, a_id;
			auto split = false;

			for (auto i = 0; i < move_info.size(); i++)
			{
				if (move_info[i] == ',')
				{
					split = true;
					i++;
				}

				if (!split)
					v_sc += move_info[i];
				else
					a_id += move_info[i];
			}

			velocity_scale_ = atof(v_sc.c_str());
			anim_id_ = atoi(a_id.c_str());

		}

		Move(const float velocity_scale, const int anim_id)
			: velocity_scale_(velocity_scale), anim_id_(anim_id)
		{}

		void execute(Entity * entity) override;


	private:
		float velocity_scale_;
		int anim_id_;
	};



	class PauseGame : public InputCommand
	{
	public:
		PauseGame()
		{}

		void execute(Entity * entity) override
		{
		}
		void idle(Entity* entity) override
		{}

	};


	class MoveCursorX : public InputCommand
	{
	public:
		MoveCursorX(std::string x)
			: was_pressed_(false), x_increment_(std::stof(x)), count_(0), frequency_(CURSOR_FREQUENCY)
		{}

		void execute(Entity * entity) override;

		void idle(Entity* entity) override
		{
			if (was_pressed_)
			{
				count_ = 0;
				frequency_ = CURSOR_FREQUENCY;
				was_pressed_ = false;
			}
		}

	private:
		bool was_pressed_;
		int x_increment_, count_, frequency_;
	};

	class MoveCursorY : public InputCommand
	{
	public:
		MoveCursorY(std::string y)
			: was_pressed_(false), y_increment_(std::stof(y)), count_(0), frequency_(CURSOR_FREQUENCY)
		{}

		void execute(Entity * entity) override;

		void idle(Entity* entity) override
		{
			if (was_pressed_)
			{
				count_ = 0;
				frequency_ = CURSOR_FREQUENCY;
				was_pressed_ = false;
			}
		}

	private:
		bool was_pressed_;
		int y_increment_, count_, frequency_;
	};

	class MakeSelection : public InputCommand
	{
	public:
		MakeSelection()
			:was_pressed_(false)
		{}

		void execute(Entity* entity) override
		{
			was_pressed_ = true;
		}

		void idle(Entity* entity) override;

	private:
		bool was_pressed_;

	};

	class Back : public InputCommand
	{
		bool was_pressed_;
	public:
		Back();

		void execute(Entity* entity) override;
		void idle(Entity* entity) override;
	};

	class LoadData : public InputCommand
	{
		bool was_pressed_;
	public:

		LoadData() = default;

		void execute(Entity* entity) override;
		void idle(Entity* entity) override;
	};

	class IChangeState : public InputCommand
	{
		int state_id_;
		bool was_pressed_;
	public:

		IChangeState(const std::string state_id)
			: state_id_(stoi(state_id)), was_pressed_(false)
		{}

		void execute(Entity* entity) override;
		void idle(Entity* entity) override;
	};

}
