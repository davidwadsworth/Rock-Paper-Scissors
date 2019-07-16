#pragma once
#include "CharacterData.h"
#include "LoadData.h"

/**
 * @author David Wadsworth
 */

class LoadCharacterData : public LoadData
{
	CharacterCollection character_collection_;
public:
	explicit LoadCharacterData(const std::string path) 
		: LoadData(path)
	{}
	CharacterCollection load();
};
