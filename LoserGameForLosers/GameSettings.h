#pragma once
#include "Animation.h"

class GameSettings
{
	std::vector<std::vector<Animation *>> player_animations_
	{
		{ new Animation(main_player_fighter_idle_1, 3, 200), new Animation(main_player_fighter_walk_left_1, 3, 200), new Animation(main_player_fighter_walk_right_1, 3, 200) } ,
		{ new Animation(main_player_square_idle_1, 3, 200), new Animation(main_player_square_walk_left_1, 3, 200), new Animation(main_player_square_walk_right_1, 3, 200) },
		{ new Animation(main_player_arms_idle_1, 3, 200), new Animation(main_player_arms_walk_left_1, 3, 200), new Animation(main_player_arms_walk_right_1, 3, 200) }
		
	};

	std::vector<MAIN_SPRITESHEET> backgrounds_ = { main_background_cave, main_background_city, main_background_hills, main_background_suburb };
public:

	std::vector<Animation *> player1_animations = player_animations_[fighter];
	std::vector<Animation *> player2_animations = player_animations_[fighter];

	int player1 = fighter;
	int player2 = fighter;
	int background = backgrounds_[city];

	void set_player_1(const int p1)
	{
		player1_animations = player_animations_[p1];
		player1 = p1;
	}

	void set_player_2(const int p2)
	{
		player2_animations = player_animations_[p2];
		player2 = p2;
	}

	void set_background(const int bg)
	{
		background = backgrounds_[bg];
	}
};
