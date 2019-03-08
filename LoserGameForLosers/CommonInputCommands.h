#pragma once
#include "ECS.h"
#include "Constants.h"
#include "InputCommand.h"

class CombatProcessor;

class EndRoundCommand : public InputCommand
{
	CombatProcessor * processor_;
public:
	EndRoundCommand()
	{}
	~EndRoundCommand()
	{}

	void execute(Entity * entity) override;
	void idle(Entity * entity) override;
};


class MoveCommand : public InputCommand
{
public:
	MoveCommand(std::string move_info)
	{
		std::string v_sc, a_id;
		bool split = false;

		for (int i = 0; i < move_info.size(); i++)
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

	~MoveCommand()
	{}


	void execute(Entity * entity) override;

	void idle(Entity* entity) override
	{}


private:
	float velocity_scale_;
	int anim_id_;
};


class SelectAttackCommand : public InputCommand
{
public:
	SelectAttackCommand(std::string att_id)
		: was_pressed_(false), attack_id_(std::stoi(att_id))
	{}

	~SelectAttackCommand()
	{}

	void execute(Entity * entity) override
	{
		was_pressed_ = true;
	}
	void idle(Entity* entity) override;

private:
	bool was_pressed_;
	int attack_id_;
};

class PauseGameCommand : public InputCommand
{
public:
	PauseGameCommand()
	{}

	void execute(Entity * entity) override
	{
	}
	void idle(Entity* entity) override
	{}

};


class MoveCursorXCommand : public InputCommand
{
public:
	MoveCursorXCommand(std::string x)
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

class MoveCursorYCommand : public InputCommand
{
public:
	MoveCursorYCommand(std::string y)
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

class ChangeRotationPoint : public InputCommand
{
	SDL_Point increment_;
public:
	ChangeRotationPoint(std::string increment_info)
	{
		std::string x, y;
		bool split = false;

		for (int i = 0; i < increment_info.size(); i++)
		{
			if (increment_info[i] == ',')
			{
				split = true;
				i++;
			}

			if (!split)
				x += increment_info[i];
			else
				y += increment_info[i];
		}

		increment_.x = atoi(x.c_str());
		increment_.y = atoi(y.c_str());
	}

	void execute(Entity * entity) override;

	void idle(Entity* entity) override {}
};


class ChangeControllerCommand : public InputCommand
{
	int controller_id_;
public:
	ChangeControllerCommand(std::string controller_id)
		: controller_id_(std::stoi(controller_id) )
	{}

	void execute(Entity * entity) override;

	void idle(Entity* entity) override {}
};

class NothingCommand : public InputCommand
{
public:
	NothingCommand() = default;

	void execute(Entity * entity) override {}

	void idle(Entity* entity) override {}
};