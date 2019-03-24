#pragma once
#include "ECS.h"
#include "Data.h"

class DataManager
{
	Manager * manager_;

	CharacterCollection character_data_;
	AtlasData atlas_data_;
	OptionsCollection options_data_;
	ControllerCollection controllers_data_;
	AudioCollection audio_data_;
public:
	explicit DataManager(Manager *manager)
		: manager_(manager)
	{}

	~DataManager() {}

	//Atlas Data
	void load_atlas_data(const char* path);
	AtlasData* get_atlas_data();

	//Character Data
	void load_character_data(const char* path);
	CharacterData* get_character_data(int id);

	//Options Data
	void load_options_data(const char* path);
	OptionsData* get_options_data(int id);

	//Controller Data
	void load_controller_data(const char* path);
	ControllerData* get_controller_data(int id);

	//Audio Data
	void load_audio_data(const char * path);
	AudioCollection* get_audio_data();

};