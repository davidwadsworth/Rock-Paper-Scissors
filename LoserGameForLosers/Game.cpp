#include "stdafx.h"
#include "Menu.h"
#include "Combat.h"
#include "GameState.h"
#include "Constants.h"
#include "Loads.h"


Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
DataManager * data = new DataManager();

GameState * current_state = nullptr;
LoadedCollections collections = LoadedCollections();

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

	data->load_data<LoadAtlasData>("data_main_textures-0_v2.xml");
	data->load_data<LoadAudioData>("data_audio_v2.xml");
	data->load_data<LoadControllerData>("data_controllers_v2.xml");
	data->load_data<LoadOptionsData>("data_options_v2.xml");
	data->load_data<LoadCharacterData>("data_characters_v2.xml");

	collections.atlas_data = AtlasCollection(data->get_load<LoadAtlasData>().load());
	collections.audio_data = AudioCollection(data->get_load<LoadAudioData>().load());
	collections.controller_data = ControllerCollection(data->get_load<LoadControllerData>().load());
	collections.options_data = OptionsCollection(data->get_load<LoadOptionsData>().load());
	collections.character_data = CharacterCollection(data->get_load<LoadCharacterData>().load());

	current_state = new Combat(&collections);
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
			current_state = new Menu(&collections);
			break;
		case STATE_COMBAT:
			current_state = new Combat(&collections);
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

	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}

