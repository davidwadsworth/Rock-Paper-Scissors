#include "stdafx.h"
#include "DataManager.h"

void DataManager::load_atlas_data(const char * path)
{
	auto atlas_data = new AtlasData(path);
	atlases_.push_back(atlas_data->load());
}

Atlas * DataManager::get_atlas(int atlas_id)
{
	return atlases_[atlas_id];
}

SpriteAddress * DataManager::get_sprite_address(int atlas_id, int sprite_address_id)
{
	return atlases_[atlas_id]->addresses[sprite_address_id];
}

void DataManager::load_character_data( const char * path)
{
	auto character_data = new CharacterData(path);
	characters_ = character_data->load();
}

Character * DataManager::get_character(int character_id)
{
	return characters_[character_id];
}

void DataManager::load_options_data(const char * path)
{
	auto options_data = new OptionsData(path);
	options_ = options_data->load();
}

Options * DataManager::get_options(int options_id)
{
	return options_[options_id];
}

void DataManager::load_controller_data(const char * path)
{
	auto controller_data = new ControllerData(path);
	controllers_ = controller_data->load();
}

Controller * DataManager::get_controller(int controller_id)
{
	return controllers_[controller_id];
}
