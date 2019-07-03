#pragma once
#include <SDL.h>

enum Combat_State
{
	combat_state_single_player,
	combat_state_multi_player,
	combat_state_debug,
};

enum Combat_Difficulty
{
	combat_difficulty_easy,
	combat_difficulty_hard
};

class Game
{
public:
	void init(const char * window_title);
	static void update();
	static void render();
	static void handle_events();
	static void set_next_state(int new_state);
	void clean();
	static bool running() { return is_running; }

	static bool is_running;
	static int state_id;

	static SDL_Renderer *renderer;
	static SDL_Event event;
	static int combat_state;
	static int combat_difficulty;

	SDL_Window *window;

	enum group_labels : std::size_t
	{
		group_characters,
		group_background,
		group_prompts,
		group_players,
		group_cursors,
		group_wipes,
		group_overlay
	};

	
};
