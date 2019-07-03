#include "stdafx.h"
#include "Menu.h"
#include "MenuPresets.h"
#include "Loads.h"

Menu::Menu(Manager * manager)
	: GameState(manager)
{
	screen_ = new Assets::MenuScreen(manager);

	auto atlas_load = LoadAtlasData("data_menu_textures-0.xml");
	auto audio_load = LoadAudioData("data_audio_v2.xml");
	auto controller_load = LoadControllerData("data_controllers_v2.xml");
	auto options_load = LoadOptionsData("data_options_v2.xml");

	set_atlas_data(new AtlasCollection(atlas_load.load()));
	set_audio_data(new AudioCollection(audio_load.load()));
	set_controller_data(new ControllerCollection(controller_load.load()));
	set_options_data(new OptionsCollection(options_load.load()));

	auto palette = new TextureManager();
	palette->load_texture(get_atlas_data()->path.c_str());
	palette->load_texture("white_background.png");
	palette->load_font("lazyfont.png");
	set_palette(palette);

	set_audio_player(new AudioQueue(get_audio_data()));

	screen_->create();

	set_path(new Path());

	auto menu_presets = MenuPresets::CreateMenuOptions(screen_->get_asset());
	menu_presets.init();
	get_path()->add(menu_presets.get_trunk());
}


void Menu::render()
{
	auto& background_group = get_manager()->get_group(Game::group_background);
	auto& cursor_group = get_manager()->get_group(Game::group_cursors);

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
	get_path()->navigate_path();

	get_manager()->refresh();
	get_manager()->update();
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
	get_path()->clear();
	get_audio_player()->close();
	get_palette()->free_textures();
	screen_->destroy();
	get_manager()->refresh();
	get_manager()->update();
}
