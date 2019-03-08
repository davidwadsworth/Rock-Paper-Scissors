#pragma once

#include "AtlasData.h"

class LoadAtlasData
{
	const char * path_;
public:
	explicit LoadAtlasData(const char * path)
		: path_(path)
	{}
	~LoadAtlasData() {}
	AtlasData load() const;
};
