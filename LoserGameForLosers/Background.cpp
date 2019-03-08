#include "stdafx.h"

/**
 * Background
 **
 * In charge of manipulating the background based on the positions of the two players
 * With some tweaks could support multiple entities
 * 
 */


void Background::screen_change()
{
	auto scroll_inc = 0.0f;
	auto scale_inc = 0.0f;
	auto external_velocity_p1 = 0.0f;
	auto external_velocity_p2 = 0.0f;

	p1_scale_ = p1_tc_->scale_2d.x;
	p2_scale_ = p2_tc_->scale_2d.x;
	bg_scale_ = bg_tc_->scale_2d.x;

	p1_position_ = p1_tc_->position;
	p2_position_ = p2_tc_->position;
	bg_position_ = bg_tc_->position;

	const auto p1_velocity = p1_pc_->get_velocity();
	const auto p2_velocity = p2_pc_->get_velocity();

	const auto p1_player_velocity_x = p1_tc_->player_velocity.x;
	const auto p2_player_velocity_x = p2_tc_->player_velocity.x;

	const auto p1_collider = p1_col_c_->collider;
	const auto p2_collider = p2_col_c_->collider;

	const auto p1_vector = p1_velocity * p1_tc_->speed;
	const auto p2_vector = p2_velocity * p2_tc_->speed;

	if (Collision::aabb(p1_collider, LEFT_EDGE)) // is left player is colliding with left side of screen
	{
		if (p1_position_.x < LEFT_EDGE.x) // is player 1 is past the edge 
			p1_position_.x = LEFT_EDGE.x;

		if (p1_player_velocity_x < 0) // is player 1 moving towards the edge
		{	
			scale_inc -= p1_vector;
			if (!Collision::aabb(p2_collider, RIGHT_EDGE)) // is player 2 not at right edge 
			{
				// some magic that makes it seem like player 1 is moving away from player 2
				scale_inc = 0;
				scroll_inc -= p1_vector;
				external_velocity_p2 += p1_velocity;
			}
			else if (p2_player_velocity_x < 0) // player 2 is colliding with the left edge and is moving towards player 2
				scroll_inc -= p1_vector;
		}
		if (p1_player_velocity_x > 0) // is player 1 moving towards player 2
		{
			scale_inc += p1_vector;
		}
	}
	if (Collision::aabb(p2_collider, RIGHT_EDGE)) // is player 2 colliding with the right side of the screen
	{
		if (p2_position_.x > RIGHT_EDGE.x + RIGHT_EDGE.w - SPRITE_LENGTH * p2_scale_)
			p2_position_.x = RIGHT_EDGE.x + RIGHT_EDGE.w - SPRITE_LENGTH * p2_scale_;

		if (p2_player_velocity_x > 0) // is player 2 moving towards the right edge 
		{
			scale_inc -= p2_vector;
			if (!Collision::aabb(p1_collider, LEFT_EDGE)) // is player 1 not at the left edge
			{
				// some magic that makes is seem like player 2 is moving away from player 1
				external_velocity_p1 -= p2_velocity;
				scale_inc = 0;
				scroll_inc += p2_vector;
			}
			else if (p1_player_velocity_x > 0) // player 1 is colliding with the edge and moving towards player 2
				scroll_inc += p2_vector;
		}
		if (p2_player_velocity_x < 0) // player 2 is moving towards player 1
		{
			scale_inc += p2_vector;
		}
	}

	// normalizes all horizontal velocity
	p1_tc_->external_velocity.x = external_velocity_p1;
	p2_tc_->external_velocity.x = external_velocity_p2;

	// adds together all the scaling increments from cycle
	scroll_screen(scroll_inc);
	scale_screen(scale_inc);

	// update changed scaling and position values
	p1_tc_->scale_2d = p1_scale_;
	p2_tc_->scale_2d = p2_scale_;
	bg_tc_->scale_2d = bg_scale_;

	p1_tc_->position = p1_position_;
	p2_tc_->position = p2_position_;
	bg_tc_->position = bg_position_;
}

void Background::scroll_screen(const float scroll_increment)
{
	bg_position_.x = (bg_position_.x - scroll_increment * bg_scale_ / SPRITE_SCALING);
	if (!(bg_position_.x > -bg_tc_->width * bg_scale_ && bg_position_.x < bg_tc_->width * bg_scale_))
		bg_position_.x = (0);

}

void Background::scale_screen(const float scale_increment)
{
	// the difference between scale bounds / the possible distance traveled by a single character * stretch speed
	const auto player_sc_range = (SPRITE_SCALING - SPRITE_SCALING_TARGET) / static_cast<float>(SCREEN_WIDTH - SPRITE_LENGTH * p1_scale_)* scale_increment * p1_scale_ / SPRITE_SCALING;
	const auto background_sc_range = (BACKGROUND_SCALING - BACKGROUND_SCALING_TARGET) / static_cast<float>(SCREEN_WIDTH - SPRITE_LENGTH * bg_scale_) * scale_increment * bg_scale_ / BACKGROUND_SCALING;

	p1_scale_ = std::min(std::max(SPRITE_SCALING_TARGET, p1_scale_ + player_sc_range), SPRITE_SCALING); // sets the scaling to a number between the target and the starting
	p1_position_.y = SCREEN_HEIGHT - SPRITE_LENGTH * p1_scale_;

	auto scaling_offset_x = p2_scale_ - p1_scale_;

	p2_scale_ =	p1_scale_;
	p2_position_.x += scaling_offset_x * SPRITE_LENGTH;
	p2_position_.y = p1_position_.y;

	const auto previous_scale_x = bg_scale_;

	bg_scale_ = std::min(std::max(BACKGROUND_SCALING_TARGET, bg_scale_ + background_sc_range), BACKGROUND_SCALING); // sets the scaling to a number between the target and the starting
	scaling_offset_x = previous_scale_x - bg_scale_;


	// sets the center of scaling to be at some distance to the player with higher velocity
	auto center_of_scaling = SCREEN_WIDTH * (0.5 + (p1_pc_->get_velocity() - p2_pc_->get_velocity()) / 2);

	if (std::fabsf(p1_tc_->player_velocity.x) <= FLT_EPSILON)
		center_of_scaling = 0;
	else if (std::fabsf(p2_tc_->player_velocity.x) <= FLT_EPSILON)
		center_of_scaling = SCREEN_WIDTH;

	// the difference in scaling from new and old backgrounds * the background width * the center of scaling
	bg_position_.x += scaling_offset_x * bg_tc_->width * (-bg_position_.x + center_of_scaling) / (BACKGROUND_WIDTH * bg_scale_);
	bg_position_.y = SCREEN_HEIGHT - bg_tc_->height * bg_scale_;
}

