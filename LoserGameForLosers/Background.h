#pragma once
#include "Components.h"
#include "Constants.h"

/**
 * @author David Wadsworth
 *
 * calculates how much the background and players have to scale/move to create the realism of movement once a player reaches the edge of the screen
*/

class Background
{
public:
	Background() = default;

	Background(Entity * player1, Entity * player2, Entity * background)
		: p1_scale_(0), p2_scale_(0), bg_scale_(0)
	{
		p1_tc_ = &player1->get_component<TransformComponent>();
		p2_tc_ = &player2->get_component<TransformComponent>();
		bg_tc_ = &background->get_component<TransformComponent>();

		p1_pc_ = &player1->get_component<PlayerComponent>();
		p2_pc_ = &player2->get_component<PlayerComponent>();

		p1_col_c_ = &player1->get_component<ColliderComponent>();
		p2_col_c_ = &player2->get_component<ColliderComponent>();
	}

	~Background() = default;

	void screen_change();
	void scroll_screen(double scroll_increment);
	void scale_screen(double scale_increment);

private:
	TransformComponent * p1_tc_;
	TransformComponent * p2_tc_;
	TransformComponent * bg_tc_;

	PlayerComponent * p1_pc_;
	PlayerComponent * p2_pc_;

	ColliderComponent * p1_col_c_;
	ColliderComponent * p2_col_c_;

	double p1_scale_, p2_scale_, bg_scale_;
	Vector2D p1_position_, p2_position_, bg_position_;

	const SDL_Rect LEFT_EDGE{ 0, 0, BACKGROUND_COLLIDER, BACKGROUND_HEIGHT };
	const SDL_Rect RIGHT_EDGE{ BACKGROUND_WIDTH - BACKGROUND_COLLIDER, 0, BACKGROUND_COLLIDER, BACKGROUND_HEIGHT };
	const double CENTER = 0.5;

};