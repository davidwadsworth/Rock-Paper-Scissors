#pragma once
#include "Data.h"
#include "ECS.h"
#include "AudioQueue.h"
#include "Pathway.h"
#include "TextureManager.h"
#include "AIData.h"

/**
 * @author David Wadsworth
 *
 * abstractly updates, draws, creates and closes the running entities of the current game
*/

class GameState
{
	static AtlasCollection* atlas_data_;
	static CharacterCollection* character_data_;
	static ControllerCollection* controller_data_;
	static OptionsCollection* options_data_;
	static AudioCollection* audio_data_;
	static AICollection* ai_data_;

	static TextureManager* palette_;
	static AudioQueue* audio_player_;
	static Path* path_;
	static Manager* manager_;
public:
	explicit GameState(Manager * manager);

	static AtlasCollection* get_atlas_data() { return atlas_data_; }
	static void set_atlas_data(AtlasCollection * data) { atlas_data_ = data; }

	static CharacterCollection* get_character_data() { return character_data_; }
	static void set_character_data(CharacterCollection * data) { character_data_ = data; }
	
	static ControllerCollection* get_controller_data() { return controller_data_; }
	static void set_controller_data(ControllerCollection * data) { controller_data_ = data; }
	
	static OptionsCollection* get_options_data() { return options_data_; }
	static void set_options_data(OptionsCollection * data) { options_data_ = data; }
	
	static AudioCollection* get_audio_data() { return audio_data_; }
	static void set_audio_data(AudioCollection * data) { audio_data_ = data; }

	static AICollection* get_ai_data() { return ai_data_; }
	static void set_ai_data(AICollection * data) { ai_data_ = data; }

	static TextureManager* get_palette() { return palette_; }
	static void set_palette(TextureManager * palette) { palette_ = palette; }

	static AudioQueue* get_audio_player() { return audio_player_; }
	static void set_audio_player(AudioQueue * audio_player) { audio_player_ = audio_player; }

	static Path * get_path() { return path_; }
	static void set_path(Path* path)
	{
		if (path_)
			path_->clear();
		path_ = path;
	}

	static Manager * get_manager() { return manager_; }
	static void set_manager(Manager* manager) { manager_ = manager; }

	virtual void logic() = 0;
	virtual void render() = 0;
	virtual void handle_events() = 0;
	virtual void close() = 0;
	virtual ~GameState() {}

};

enum game_states
{
	STATE_NULL,
	STATE_MENU,
	STATE_VIDEO,
	STATE_OVERWORLD,
	STATE_COMBAT,
	STATE_EXIT
};
