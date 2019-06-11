#include "stdafx.h"
#include "Menu.h"
#include "PathHack.h"



Menu::Menu(LoadedCollections * collections)
	: GameState(collections)
{
	palette = new AssetManager(&manager, this);
	palette->add_texture(collections->atlas_data.path.c_str());
	palette->add_texture("white_background.png");
	palette->set_bit_map_font("lazyfont.png");
	audio_player = new AudioQueue(&bank->audio_data);

	const auto menu = palette->create_menu_screen();
	path = new Path();

	auto hack = PathHack(this);

	path->add(hack.initiate_menu());

}


void Menu::render()
{
	auto& background_group = manager.get_group(Game::group_background);
	auto& cursor_group = manager.get_group(Game::group_cursors);

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

	manager.refresh();
	manager.update();
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
	for (auto& b : manager.get_group(Game::group_background))
	{
		b->del_group(Game::group_background);
		b->destroy();
	}
	for (auto& c : manager.get_group(Game::group_cursors))
	{
		c->del_group(Game::group_cursors);
		c->destroy();
	}

	audio_player->stop_music();
}
