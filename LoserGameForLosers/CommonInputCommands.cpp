#include "stdafx.h"
#include "CommonInputCommands.h"
#include "CombatPresets.h"
#include "LoadCharacterData.h"


namespace InputCommands
{
	void Move::execute(Entity * entity)
	{
		const auto transform = &entity->get_component<TransformComponent>();
		transform->player_velocity.x = velocity_scale_ * entity->get_component<PlayerComponent>().get_velocity();
		transform->net_velocity.x = 0.0f;
		entity->get_component<SpriteComponent>().play_animation(anim_id_);

		if (transform->scale == SPRITE_SCALING)
			transform->net_velocity.x = transform->player_velocity.x + transform->external_velocity.x;
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

	Back::Back()
		: was_pressed_(false)
	{}

	void Back::execute(Entity * entity)
	{
		was_pressed_ = true;
	}

	void Back::idle(Entity * entity)
	{
		if (was_pressed_)
		{
			GameState::get_path()->previous_path();
		}
	}

	void LoadData::execute(Entity * entity)
	{
		was_pressed_ = true;
	}

	void LoadData::idle(Entity * entity)
	{
		if (was_pressed_)
		{
			auto character_data = new LoadCharacterData("data_characters_v2.xml");
			GameState::set_character_data(new CharacterCollection(character_data->load()));
			delete character_data;
		}
	}

	void IChangeState::execute(Entity * entity)
	{
		was_pressed_ = true;
	}

	void IChangeState::idle(Entity * entity)
	{
		if (was_pressed_)
		{
			Game::set_next_state(state_id_);
			was_pressed_ = false;
		}
	}

}


