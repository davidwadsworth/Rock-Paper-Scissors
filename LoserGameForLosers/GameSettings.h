#pragma once

class GameSettings
{
	std::vector<MAIN_SPRITESHEET> players_ = { main_player_fighter_idle_1, main_player_square_idle_1, main_player_arms_idle_1 };
	std::vector<MAIN_SPRITESHEET> backgrounds_ = { main_background_cave, main_background_city, main_background_hills, main_background_suburb };
public:

	int player_1_texture = players_[fighter];
	int player_2_texture = players_[fighter];

	int player_1_info = fighter;
	int player_2_info = fighter;
	int background = backgrounds_[city];

	void set_player_1(const int p1)
	{
		player_1_texture = players_[p1];
		player_1_info = p1;
	}

	void set_player_2(const int p2)
	{
		player_2_texture = players_[p2];
		player_2_info = p2;
	}

	void set_background(const int bg)
	{
		background = backgrounds_[bg];
	}
};
