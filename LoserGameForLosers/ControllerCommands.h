#pragma once
#include "ECS.h"
#include "Constants.h"
#include "SpriteComponent.h"
#include "PlayerComponent.h"
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
			if (move_str.at[i] == ',')
			{
				split = true;
				i++;
			}

			if (!split)
				v_sc += move_str.at[i];
			else
				a_id += move_str.at[i];
		}

		velocity_scale_ = atof(v_sc.c_str);
		anim_id_ = atoi(a_id.c_str);

	}

	~MoveCommand()
	{}


	void execute(Entity * entity) override
	{
		auto transform = &entity->get_component<TransformComponent>();
		transform->player_velocity.x = velocity_scale_ * entity->get_component<PlayerComponent>().get_velocity();
		transform->net_velocity.x = 0.0f;
		entity->get_component<SpriteComponent>().play(anim_id_);
		
		if (transform->scale == SPRITE_SCALING)
			transform->net_velocity.x = transform->player_velocity.x + transform->external_velocity.x;
	}

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
	void idle(Entity* entity) override
	{
		if (was_pressed_)
		{
			entity->get_component<PlayerComponent>().choose_attack(attack_id_);
			was_pressed_ = false;
		}
	}

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

	void execute(Entity * entity) override
	{
		was_pressed_ = true;

		if (count_% frequency_ == 0)
		{
			const auto options = &entity->get_component<OptionsComponent>();
			options->next_x(x_increment_);
			frequency_ = std::max(frequency_ - 1, 1);
		}
		count_++;
	}

	void idle(Entity* entity) override
	{
		if (was_pressed_)
		{
			const auto options = &entity->get_component<OptionsComponent>();
			options->next_x(x_increment_);
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

	void execute(Entity * entity) override
	{
		if (count_% frequency_ == 0)
		{
			const auto options = &entity->get_component<OptionsComponent>();
			options->next_y(y_increment_);
			frequency_ = std::max(frequency_ - 3, 3);
		}
		was_pressed_ = true;
		count_++;
	}

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

	void idle(Entity* entity) override
	{
		if (was_pressed_)
		{
			auto options = &entity->get_component<OptionsComponent>();
			options->get_current_link()->get_command()->execute(entity);
			was_pressed_ = false;
		}
	}

private:
	bool was_pressed_;

};


