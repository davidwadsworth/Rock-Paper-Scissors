#include "stdafx.h"
#include "GameState.h"

AtlasCollection* GameState::atlas_data_ = nullptr;
CharacterCollection* GameState::character_data_ = nullptr;
ControllerCollection* GameState::controller_data_ = nullptr;
OptionsCollection* GameState::options_data_ = nullptr;
AudioCollection* GameState::audio_data_ = nullptr;

TextureManager* GameState::palette_ = nullptr;
Path* GameState::path_ = nullptr;
AudioQueue* GameState::audio_player_ = nullptr;
Manager* GameState::manager_ = nullptr;

GameState::GameState(Manager * manager)
{
	set_manager(manager);
}
