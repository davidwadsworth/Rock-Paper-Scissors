
#include "stdafx.h"
#include "Combat.h"
#include "CombatScripts.h"
#include "Loads.h"

Combat::Combat(Manager* manager) 
	: GameState(manager)
{
	auto atlas_load = LoadAtlasData("data_main_textures-0_v2.xml");
	auto audio_load = LoadAudioData("data_audio_v2.xml");
	auto controller_load = LoadControllerData("data_controllers_v2.xml");
	auto options_load = LoadOptionsData("data_options_v2.xml");
	auto character_load = LoadCharacterData("data_characters_v2.xml");

	bank->atlas_data = new AtlasCollection(atlas_load.load());
	bank->audio_data = new AudioCollection(audio_load.load());
	bank->controller_data = new ControllerCollection(controller_load.load());
	bank->options_data = new OptionsCollection(options_load.load());
	bank->character_data = new CharacterCollection(character_load.load());

	palette = new AssetManager(manager, this);
	palette->add_texture(bank->atlas_data->path.c_str());
	palette->add_texture("white_background.png");
	palette->set_bit_map_font("lazyfont.png");
	audio_player = new AudioQueue(bank->audio_data);

	const auto player_left = palette->create_left_player(controller_debug);
	const auto player_right = palette->create_right_player(controller_debug);
	const auto background = palette->create_combat_background();
/*
	path = new CombatScripts::Debug();*/
	bg_logic_ = new Background(player_left, player_right, background);
}

Combat::~Combat()
{
	Combat::close();
}

void Combat::logic()
{
	bg_logic_->screen_change();
	manager->refresh();
	manager->update();
/*
	path->navigate_path();*/
}

void Combat::render()
{
	auto& background_group = manager->get_group(Game::group_background);
	auto& prompt_group = manager->get_group(Game::group_prompts);
	auto& cursor_group = manager->get_group(Game::group_cursors);
	auto& player_group = manager->get_group(Game::group_players);

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
}

void Combat::handle_events()
{
	SDL_PollEvent(&Game::event);

	switch (Game::event.type)
	{
	case SDL_QUIT:
		Game::is_running = false;
		break;

	default:
		break;
	}
}

void Combat::close()
{/*
	path->clear();*/

	for (auto& b : manager->get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}

	for (auto& p : manager->get_group(Game::group_players))
	{
		p->del_group(Game::group_players);
		p->destroy();
	}

	for (auto& pr : manager->get_group(Game::group_prompts))
	{
		pr->del_group(Game::group_prompts);
		pr->destroy();
	}
	for (auto& c : manager->get_group(Game::group_cursors))
	{
		c->del_group(Game::group_cursors);
		c->destroy();
	}

	bg_logic_ = nullptr;
	manager = nullptr;
	bank = nullptr;
	palette = nullptr;
	audio_player->stop_music();
	audio_player = nullptr;
}




