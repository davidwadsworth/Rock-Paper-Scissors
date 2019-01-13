#pragma once
#include <rapidxml.hpp>
#include "constants.h"
#include "character.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class CharacterData
{
	const char * path_;
public:
	CharacterData(const char * path) 
		: path_(path)
	{}
	~CharacterData() {}
	std::vector<Character*> load();
};