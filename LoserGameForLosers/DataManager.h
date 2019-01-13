#pragma once
#include "ECS.h"
#include "Data.h"
#include <map>

class DataManager
{
	Manager * manager_;

	std::vector<Character *> characters_;
	std::vector<Atlas *> atlases_;
	std::vector<Options *> options_;
	std::vector<Controller *> controllers_;

public:
	DataManager(Manager *manager)
		: manager_(manager)
	{}
	~DataManager() {}


	//Atlas Data
	void load_atlas_data(const char* path);
	Atlas* get_atlas(int atlas_id);
	SpriteAddress* get_sprite_address(int atlas_id, int sprite_address_id);

	//Character Data
	void load_character_data(const char* path);
	Character* get_character(int character_id);

	//Options Data
	void load_options_data(const char* path);
	Options* get_options(int options_id);

	//Controller Data
	void load_controller_data(const char* path);
	Controller* get_controller(int controller_id);
};