#include "stdafx.h"
#include "DataManager.h"
#include "DataLoads.h"

void DataManager::load_atlas_data(const char * path)
{
	auto atlas_data = LoadAtlasData(path);
	atlas_data_ = atlas_data.load();
}

AtlasData* DataManager::get_atlas_data()
{
	return &atlas_data_;
}

void DataManager::load_character_data( const char * path)
{
	auto character_data = LoadCharacterData(path);
	character_data_ = character_data.load();
}

CharacterData *DataManager::get_character_data(int id)
{
	return &character_data_.data[id];
}

void DataManager::load_options_data(const char * path)
{
	auto options_data = LoadOptionsData(path);
	options_data_ = options_data.load();
}

OptionsData *DataManager::get_options_data(int id)
{
	return &options_data_.data[id];
}

void DataManager::load_controller_data(const char * path)
{
	auto controller_data = LoadControllerData(path);
	controllers_data_ = controller_data.load();
}

ControllerData *DataManager::get_controller_data(int id)
{
	return &controllers_data_.data[id];
}

void DataManager::load_audio_data(const char * path)
{
	auto audio_data = LoadAudioData(path);
	audio_data_ = audio_data.load();
}

AudioCollection * DataManager::get_audio_data()
{
	return &audio_data_;
}
