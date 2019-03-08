#pragma once
#include "CharacterData.h"

class LoadCharacterData
{
	const char * path_;
public:
	LoadCharacterData(const char * path) 
		: path_(path)
	{}
	~LoadCharacterData() {}
	CharacterCollection load() const;
};
