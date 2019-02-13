#include "stdafx.h"
#include "Menu.h"
#include "Combat.h"
#include "GameState.h"
#include "Constants.h"
#include "DataBank.h"



Manager manager;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
GameSettings* Game::game_settings = new GameSettings();

BitmapFont font;
BitmapTexture bitmaptex;


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

	if (bitmaptex.load_from_file("lazyfont.png"))
	{
		font.build_font(&bitmaptex);
	}
	else { std::cout << "Font Failure" << std::endl; }

	assets->set_bit_map_font("lazyfont.png");

	data->load_atlas_data("data_main_textures-0_v1.xml");
	data->load_character_data("data_characters_v1.xml");
	data->load_controller_data("data_controllers_v1.xml");
	data->load_options_data("data_options_v1.xml");

	Game::game_settings->player1 = data->get_character(arms);
	Game::game_settings->player2 = data->get_character(fighter);

	Game::assets->add_texture(data->get_atlas(atlas_texture_sheet_main)->path.c_str());



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

void Game::render()
{
	SDL_RenderClear(renderer);
	current_state->render();
	Game::assets->get_bitmap_font()->render_text(0, 0, "Bitmap Font:\nABDCEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz\n0123456789");
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

