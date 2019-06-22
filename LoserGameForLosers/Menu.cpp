#include "stdafx.h"
#include "Menu.h"
#include "MenuPresets.h"
#include "Loads.h"

Menu::Menu(Manager * manager)
	: GameState(manager)
{
	auto atlas_load = LoadAtlasData("data_menu_textures-0.xml");
	auto audio_load = LoadAudioData("data_audio_v2.xml");
	auto controller_load = LoadControllerData("data_controllers_v2.xml");
	auto options_load = LoadOptionsData("data_options_v2.xml");

	bank->atlas_data = new AtlasCollection(atlas_load.load());
	bank->audio_data = new AudioCollection(audio_load.load());
	bank->controller_data = new ControllerCollection(controller_load.load());
	bank->options_data = new OptionsCollection(options_load.load());

	palette = new AssetManager(manager, this);
	palette->add_texture(bank->atlas_data->path.c_str());
	palette->add_texture("white_background.png");
	palette->set_bit_map_font("lazyfont.png");
	audio_player = new AudioQueue(bank->audio_data);

	const auto menu = palette->create_menu_screen();
	path = new Path();

	auto menu_presets = MenuPresets::CreateMenuOptions(this);
	menu_presets.init();
	path->add(menu_presets.get_trunk());
}


void Menu::render()
{
	auto& background_group = manager->get_group(Game::group_background);
	auto& cursor_group = manager->get_group(Game::group_cursors);

	for (auto& b : background_group)
	{
		b->draw();
	}
	for (auto& c : cursor_group)
	{
		c->draw();
	}
}

void Menu::logic()
{
	path->navigate_path();

	manager->refresh();
	manager->update();
}

void Menu::handle_events()
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

void Menu::close()
{
	for (auto& b : manager->get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}
	for (auto& c : manager->get_group(Game::group_cursors))
	{
		c->del_group(Game::group_cursors);
		c->destroy();
	}

	audio_player->stop_music();
}
