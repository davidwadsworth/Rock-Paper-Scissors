#pragma once

class GameSettings
{
	std::vector<MAIN_SPRITESHEET> players_ = { main_player_fighter_idle_1, main_player_square_idle_1, main_player_arms_idle_1 };
	std::vector<MAIN_SPRITESHEET> backgrounds_ = { main_background_cave, main_background_city, main_background_hills, main_background_suburb };
	std::vector<std::vector<SDL_Scancode>> input_keys_ = {
		{
			SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_1, SDL_SCANCODE_2,
			SDL_SCANCODE_3, SDL_SCANCODE_4
		},
		{
			SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_I, SDL_SCANCODE_O,
			SDL_SCANCODE_P, SDL_SCANCODE_L
		}
	};
public:

	int player_1_texture = players_[fighter];
	int player_2_texture = players_[fighter];

	int player_1_info = fighter;
	int player_2_info = fighter;
	int background = backgrounds_[city];
	std::vector<SDL_Scancode> player_1_keys = input_keys_[0];
	std::vector<SDL_Scancode> player_2_keys = input_keys_[1];
	int game_mode = 0;

	void set_player_1(const int p1)
	{
		player_1_texture = players_[p1];
		player_1_info = p1;
	}

	std::vector<SDL_Scancode> get_keys(const int keys_id)
	{
		return input_keys_[keys_id];
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
