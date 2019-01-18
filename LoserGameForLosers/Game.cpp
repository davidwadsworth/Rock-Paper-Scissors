#include "stdafx.h"
#include "Menu.h"
#include "Combat.h"
#include "GameState.h"
#include "Constants.h"



Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
GameSettings* Game::game_settings = new GameSettings();

AssetManager* Game::assets = new AssetManager(&manager);
DataManager * Game::data = new DataManager(&manager);

GameState * current_state = nullptr;

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

	data->load_atlas_data("data_main_textures-0.xml");
	data->load_atlas_data("data_prompts-0.xml");
	data->load_character_data("data_characters.xml");
	data->load_controller_data("data_controllers.xml");
	data->load_options_data("data_options.xml");

	Game::game_settings->player1 = data->get_character(square);
	Game::game_settings->player2 = data->get_character(arms);

	Game::assets->add_texture(data->get_atlas(atlas_texture_sheet_main)->path.c_str());
	Game::assets->add_texture(data->get_atlas(atlas_texture_sheet_prompts)->path.c_str());

	Game::assets->set_bit_map_font("lazyfont.png");

	current_state = new Combat(&manager);
	state_id = STATE_COMBAT;
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

void Game::render()
{
	SDL_RenderClear(renderer);
	current_state->render();
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
