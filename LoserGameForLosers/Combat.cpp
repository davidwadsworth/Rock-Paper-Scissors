
#include "stdafx.h"
#include "Combat.h"
#include "CombatScripts.h"
#include "Loads.h"

Background * bg_logic;

Combat::Combat(Manager* manager) 
	: GameState(manager)
{
	player_1_ = new Assets::PlayerLeft(manager);
	player_2_ = new Assets::PlayerRight(manager);
	background_ = new Assets::CombatBackground(manager);
	left_overlay_ = new Assets::Overlay(manager);
	right_overlay_ = new Assets::Overlay(manager);

	auto atlas = new LoadAtlasData("data_main_textures-0_v2.xml");
	auto audio = new LoadAudioData("data_audio_v2.xml");
	auto controller = new LoadControllerData("data_controllers_v2.xml");
	auto options = new LoadOptionsData("data_options_v2.xml");
	auto character = new LoadCharacterData("data_characters_v2.xml");

	set_atlas_data(new AtlasCollection(atlas->load()));
	set_audio_data(new AudioCollection(audio->load()));
	set_controller_data(new ControllerCollection(controller->load()));
	set_options_data(new OptionsCollection(options->load()));
	set_character_data(new CharacterCollection(character->load()));

	auto palette = new TextureManager();
	palette->load_texture(get_atlas_data()->path);
	palette->load_texture("gray_background.png");
	palette->load_font("lazyfont.png");
	set_palette(palette);

	set_audio_player(new AudioQueue(get_audio_data()));

	background_->create();
	left_overlay_->create(ss_main_health_container, ss_main_health_bar, SDL_FLIP_NONE);
	right_overlay_->create(ss_main_health_container, ss_main_health_bar, SDL_FLIP_HORIZONTAL);

	player_1_->create(controller_combat);
	player_2_->create(controller_combat, Game::combat_difficulty);

	switch (Game::combat_state)
	{
	case combat_state_single_player:
		set_path(new CombatScripts::SinglePlayer(player_1_->get_asset(), player_2_->get_asset(), background_->get_asset()));
		break;
	case combat_state_multi_player:
		set_path(new CombatScripts::MultiPlayer(player_1_->get_asset(), player_2_->get_asset(), background_->get_asset()));
		break;
	default:
		set_path(new CombatScripts::Debug());
		break;
	}
	 

	bg_logic = new Background(player_1_->get_asset(), player_2_->get_asset(), background_->get_asset());

	delete atlas;
	delete audio;
	delete controller;
	delete options;
	delete character;
}

Combat::~Combat()
{
	Combat::close();
}

void Combat::logic()
{	
	bg_logic->screen_change();
	get_manager()->refresh();
	get_manager()->update();
	get_path()->navigate_path();
}

void Combat::render()
{
	auto& background_group = get_manager()->get_group(Game::group_background);
	auto& prompt_group = get_manager()->get_group(Game::group_prompts);
	auto& cursor_group = get_manager()->get_group(Game::group_cursors);
	auto& player_group = get_manager()->get_group(Game::group_players);
	auto& overlay_group = get_manager()->get_group(Game::group_overlay);

	for (auto& b : background_group)
	{
		b->draw();
	}
	for (auto& p : player_group)
	{
		p->draw();
	}
	for (auto& o : overlay_group)
	{
		o->draw();
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
{
	get_path()->clear();
	get_audio_player()->close();
	get_palette()->free_textures();
	player_1_->destroy();
	player_2_->destroy();
	background_->destroy();
	left_overlay_->destroy();
	right_overlay_->destroy();
	get_manager()->refresh();
	get_manager()->update();
}




