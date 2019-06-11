#pragma once
#include "CharacterData.h"

class LoadCharacterData : public LoadData
{
public:
	LoadCharacterData(const std::string path) 
		: LoadData(path)
	{}
	~LoadCharacterData() {}
	CharacterCollection load() const;
};
