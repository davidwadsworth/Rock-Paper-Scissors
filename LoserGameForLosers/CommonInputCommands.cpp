#include "stdafx.h"
#include "CommonInputCommands.h"


namespace InputCommands
{
	void Move::execute(Entity * entity)
	{
		const auto transform = &entity->get_component<TransformComponent>();
		transform->player_velocity.x = velocity_scale_ * entity->get_component<PlayerComponent>().get_velocity();
		transform->net_velocity.x = 0.0f;
		entity->get_component<SpriteComponent>().play(anim_id_);

		if (transform->scale_2d.x == SPRITE_SCALING)
			transform->net_velocity.x = transform->player_velocity.x + transform->external_velocity.x;
	}

	void SelectAttack::idle(Entity * entity)
	{
		if (was_pressed_)
		{
			entity->get_component<PlayerComponent>().choose_attack(attack_id_);
			was_pressed_ = false;
		}
	}

	void MoveCursorX::execute(Entity * entity)
	{
		was_pressed_ = true;

		if (count_% frequency_ == 0)
		{
			auto options = &entity->get_component<OptionsComponent>();
			options->next_x(x_increment_);
			frequency_ = std::max(frequency_ - 1, 1);
		}
		count_++;
	}


	void MoveCursorY::execute(Entity * entity)
	{
		if (count_% frequency_ == 0)
		{
			auto options = &entity->get_component<OptionsComponent>();
			options->next_y(y_increment_);
			frequency_ = std::max(frequency_ - 3, 3);
		}
		was_pressed_ = true;
		count_++;
	}

	void MakeSelection::idle(Entity * entity)
	{
		if (was_pressed_)
		{
			entity->get_component<OptionsComponent>().make_selection();
			was_pressed_ = false;
		}
	}

	void ChangeController::execute(Entity * entity)
	{
		entity->get_component<ControllerComponent>().change_controller(controller_id_);
	}
}


