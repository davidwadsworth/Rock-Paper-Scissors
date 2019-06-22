#pragma once
#include "AtlasData.h"
#include "CharacterData.h"
#include "ControllerData.h"
#include "OptionsData.h"
#include "AudioData.h"

struct LoadedCollections
{
	AtlasCollection * atlas_data;
	CharacterCollection * character_data;
	ControllerCollection * controller_data;
	OptionsCollection * options_data;
	AudioCollection * audio_data;
};