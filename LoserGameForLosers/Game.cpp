#include "stdafx.h"
#include "Menu.h"
#include "Combat.h"
#include "GameState.h"
#include "CharacterDataReader.h"


Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
GameSettings* Game::game_settings = new GameSettings();

AssetManager* Game::assets = new AssetManager(&manager);
GameState * current_state = nullptr;

BitmapTexture tex;
BitmapFont font;

CharacterDataReader * char_data;

bool Game::is_running = false;



//State variables
int Game::state_id = STATE_NULL;
int next_state = STATE_NULL;

void Game::init(const char * window_title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		Game::is_running = true;
	}

	char_data = new CharacterDataReader("data_characters.xml");

	Game::game_settings->player1 = char_data->load(square);
	Game::game_settings->player2 = char_data->load(arms);


	// needs to be moved to a single png, so I can gloat about effieciancy
	Game::assets->add_texture("background", "western industrial.jpg");
	Game::assets->add_texture("player left", "square_full.png");
	Game::assets->add_texture("player right", "LongArms_full.png");

	Game::assets->set_bit_map_font("lazyfont.png");

	Game::assets->add_texture("main", "title_screen.png");
	Game::assets->add_texture("box", "textbox.png");
	Game::assets->add_texture("cursor", "cursor.png");

	Game::assets->add_texture("round", "prompt_round.png");
	Game::assets->add_texture("number", "numbers.png");
	Game::assets->add_texture("select attack", "prompt_select_attack.png");
	Game::assets->add_texture("miss", "prompt_miss.png");
	Game::assets->add_texture("stop", "prompt_stop.png" );
	Game::assets->add_texture("fight", "prompt_fight.png");

	Game::assets->add_texture("player 1 wins", "prompt_player_1_wins.png");
	Game::assets->add_texture("player 2 wins", "prompt_player_2_wins.png");

	Game::assets->add_texture("player 1 match win", "prompt_player_1_match_win.png");
	Game::assets->add_texture("player 2 match win", "prompt_player_2_match_win.png");

	current_state = new Menu(&manager);
	state_id = STATE_MENU;
}

// Stolen verbatim from @LazyFooProductions
void Game::set_next_state(const int new_state)
{
	//Set the next state
	next_state = new_state;
}

// Stolen verbatim from @LazyFooProductions
void change_state()
{
	//If the state needs to be changed
	if (next_state != STATE_NULL)
	{
		//Delete the current state
		if (next_state != STATE_EXIT)
		{
			current_state->close();
			current_state = nullptr;
		}

		//Change the state
		switch (next_state)
		{
		case STATE_MENU:
			current_state = new Menu(&manager);
			break;
		case STATE_COMBAT:
			current_state = new Combat(&manager);
			break;
		default: ;
		}

		//Change the current state ID
		Game::state_id = next_state;

		//NULL the next state ID
		next_state = STATE_NULL;
	}
}

void Game::update()
{
	change_state();
	current_state->logic();
}

auto& player_group = manager.get_group(Game::group_players);
auto& background_group = manager.get_group(Game::group_background);
auto& prompt_group = manager.get_group(Game::group_prompts);
auto& cursor_group = manager.get_group(Game::group_cursors);

void Game::render()
{
	SDL_RenderClear(renderer);
	for (auto& b : background_group)
	{
		b->draw();
	}
	for (auto& p : player_group)
	{
		p->draw();
	}
	for (auto& pr : prompt_group)
	{
		pr->draw();
	}
	for (auto& c : cursor_group)
	{
		c->draw();
	}
	SDL_RenderPresent(renderer);
}

void Game::handle_events()
{
	current_state->handle_events();
}

void Game::clean()
{
	current_state->close();

	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_DestroyRenderer(renderer);

	IMG_Quit();
	SDL_Quit();
}

