#include "ControllerCommands.h"
#include "stdafx.h"

void EndRoundCommand::execute(Entity * entity)
{
}

void MoveCommand::execute(Entity * entity)
{
	auto transform = &entity->get_component<TransformComponent>();
	transform->player_velocity.x = velocity_scale_ * entity->get_component<PlayerComponent>().get_velocity();
	transform->net_velocity.x = 0.0f;
	entity->get_component<SpriteComponent>().play(anim_id_);

	if (transform->scale == SPRITE_SCALING)
		transform->net_velocity.x = transform->player_velocity.x + transform->external_velocity.x;
}

void SelectAttackCommand::idle(Entity * entity)
{
	if (was_pressed_)
	{
		entity->get_component<PlayerComponent>().choose_attack(attack_id_);
		was_pressed_ = false;
	}
}

void MoveCursorXCommand::execute(Entity * entity)
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


void MoveCursorYCommand::execute(Entity * entity)
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
		auto options = &entity->get_component<OptionsComponent>();
		options->get_current_link()->get_command()->execute(entity);
		was_pressed_ = false;
	}
}

void ChangeRotationPoint::execute(Entity * entity)
{
	auto sprite = &entity->get_component<SpriteComponent>();
	sprite->rotation_point.x += increment_.x;
	sprite->rotation_point.y += increment_.y;
	std::cout << "( " << sprite->rotation_point.x << ", " << sprite->rotation_point.y << ")" << std::endl;
}

void ChangeControllerCommand::execute(Entity * entity)
{
	entity->get_component<ControllerComponent>().change_controller(controller_id_);
	std::cout << "Changed controller" << std::endl;
}
