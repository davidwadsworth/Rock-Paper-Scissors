#include "stdafx.h"

void ProjectileComponent::init()
{
	texture_ = &entity->get_component<TextureAtlasComponent>();
	player_transform_ = &player_->get_component<TransformComponent>();

	const auto player_position = player_transform_->position;

	Projectile projectile_1;
	Projectile projectile_2;

	switch (player_->get_component<PlayerComponent>().attack_id)
	{
	case Whip:
		projectile_1.position_offset = Vector2D{0, WHIP_HEIGHT};
		projectile_1.direction = Vector2D{ 1, 0 };
		projectile_1.slots.push_back(texture_->create_image_slot(main_attack_belt_extension, player_position.x, player_position.y + WHIP_HEIGHT, 0, player_->get_component<SpriteComponent>().sprite_flip));
		projectile_1.slots.push_back(texture_->create_animated_slot(player_position.x + ATTACK_LENGTH, player_position.y + WHIP_HEIGHT * player_transform_->scale_2d.y, 200, 2, main_attack_belt_hit, 0, player_->get_component<SpriteComponent>().sprite_flip));
		projectiles_.push_back(projectile_1);
		break;
	case Jump_Kick:
		projectile_1.position_offset = Vector2D{ 0, JUMP_KICK_HEIGHT };
		projectile_1.direction = Vector2D{ 1, 0 };
		projectile_1.slots.push_back(texture_->create_image_slot(main_attack_leg_extension, player_position.x, player_position.y + JUMP_KICK_HEIGHT, 0, player_->get_component<SpriteComponent>().sprite_flip));
		projectile_1.slots.push_back(texture_->create_animated_slot(player_position.x + ATTACK_LENGTH, player_position.y + JUMP_KICK_HEIGHT * player_transform_->scale_2d.y, 200, 2, main_attack_leg_hit, 0, player_->get_component<SpriteComponent>().sprite_flip));
		projectiles_.push_back(projectile_1);
		break;
	case Grab:
		projectile_1.position_offset = Vector2D{ 0, GRAB_HEIGHT };
		projectile_1.direction = Vector2D{ 1, 0 };
		projectile_1.slots.push_back(texture_->create_image_slot(main_attack_hand_extension, player_position.x, player_position.y + GRAB_HEIGHT, 0, player_->get_component<SpriteComponent>().sprite_flip));
		projectile_1.slots.push_back(texture_->create_animated_slot(player_position.x + ATTACK_LENGTH, player_position.y + GRAB_ARM_SEPERATION * player_transform_->scale_2d.y, 200, 2, main_attack_leg_hit, 0, player_->get_component<SpriteComponent>().sprite_flip));
		projectiles_.push_back(projectile_1);
		projectile_2.position_offset = Vector2D{ 0, GRAB_ARM_SEPERATION };
		projectile_2.direction = Vector2D{ 1, 0 };
		projectile_2.slots.push_back(texture_->create_image_slot(main_attack_hand_extension, player_position.x, player_position.y + GRAB_HEIGHT, 0, player_->get_component<SpriteComponent>().sprite_flip));
		projectile_2.slots.push_back(texture_->create_animated_slot(player_position.x + ATTACK_LENGTH, player_position.y + GRAB_ARM_SEPERATION * player_transform_->scale_2d.y, 200, 2, main_attack_leg_hit, 0, player_->get_component<SpriteComponent>().sprite_flip));
		projectiles_.push_back(projectile_2);
		break;
	default:
		break;
	}
}

void ProjectileComponent::update()
{
	if (attack_distance_ < projectile_size_)
		for (auto& projectile : projectiles_)
		{
			
		}
		

}
