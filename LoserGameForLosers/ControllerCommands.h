#pragma once
#include "ECS.h"
#include "Constants.h"
#include "Command.h"

class CombatProcessor;

class EndRoundCommand : public Command
{
	CombatProcessor * processor_;
public:
	EndRoundCommand(CombatProcessor * processor)
		: processor_(processor)
	{}
	~EndRoundCommand()
	{}

	void execute(Entity * entity) override;
};


class MoveCommand : public Command
{
public:
	MoveCommand(const char * move_info)
	{
		std::string move_str(move_info);
		std::string v_sc, a_id;
		bool split = false;

		for (int i = 0; i < move_str.size(); i++)
		{
			if (move_str[i] == ',')
			{
				split = true;
				i++;
			}

			if (!split)
				v_sc += move_str[i];
			else
				a_id += move_str[i];
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


class SelectAttackCommand : public Command
{
public:
	SelectAttackCommand(const char * att_id)
		: was_pressed_(false), attack_id_(atoi(att_id))
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

class PauseGameCommand : public Command
{
public:
	PauseGameCommand()
	{}

	void execute(Entity * entity) override
	{
	}
	void idle(Entity* entity) override
	{}


private:
};


class MoveCursorXCommand : public Command
{
public:
	MoveCursorXCommand(const char * x)
		: was_pressed_(false), x_increment_(atof(x)), count_(0), frequency_(CURSOR_FREQUENCY)
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

class MoveCursorYCommand : public Command
{
public:
	MoveCursorYCommand(const char * y)
		: was_pressed_(false), y_increment_(atof(y)), count_(0), frequency_(CURSOR_FREQUENCY)
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

class MakeSelection : public Command
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

class ChangeRotationPoint : public Command
{
	SDL_Point increment_;
public:
	ChangeRotationPoint(const char * increment_info)
	{
		std::string move_str(increment_info);
		std::string x, y;
		bool split = false;

		for (int i = 0; i < move_str.size(); i++)
		{
			if (move_str[i] == ',')
			{
				split = true;
				i++;
			}

			if (!split)
				x += move_str[i];
			else
				y += move_str[i];
		}

		increment_.x = atoi(x.c_str());
		increment_.y = atoi(y.c_str());
	}

	void execute(Entity * entity) override;

	void idle(Entity* entity) override {}
};


class ChangeControllerCommand : public Command
{
	int controller_id_;
public:
	ChangeControllerCommand(const char * controller_id)
		: controller_id_(atoi(controller_id) )
	{}

	void execute(Entity * entity) override;

	void idle(Entity* entity) override {}
};