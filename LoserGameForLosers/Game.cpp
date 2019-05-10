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
AudioQueue * Game::audio_queue = nullptr;
Path * Game::path = new Path();

GameState * current_state = nullptr;

Mix_Music* music = nullptr;

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

		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != -1)
		{
			is_running = true;
		}
	}

	assets->set_bit_map_font("lazyfont.png");

	data->load_atlas_data("data_main_textures-0_v1.xml");
	data->load_character_data("data_characters_v1.xml");
	data->load_controller_data("data_controllers_v1.xml");
	data->load_options_data("data_options_v1.xml");
	data->load_audio_data("data_audio_v1.xml");

	assets->add_texture(data->get_atlas_data()->image_path.c_str());
	audio_queue = new AudioQueue(data->get_audio_data());
	
	current_state = new Menu();
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
			current_state = new Menu();
			break;
		case STATE_COMBAT:
			current_state = new Combat();
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


auto& wipe_group = manager.get_group(Game::group_wipes);

void Game::render()
{
	SDL_RenderClear(renderer);
	current_state->render();

	for (auto& w : wipe_group)
	{
		w->draw();
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
	Mix_HaltMusic();

	Mix_FreeMusic(music);
	music = nullptr;

	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

