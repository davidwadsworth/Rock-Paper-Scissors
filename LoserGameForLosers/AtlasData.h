#pragma once
#include "Atlas.h"
#include <rapidxml.hpp>
#include "constants.h"
#include "character.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

class AtlasData
{
	const char * path_;
public:
	AtlasData(const char * path)
		: path_(path)
	{}
	~AtlasData() {}
	Atlas * load();
};