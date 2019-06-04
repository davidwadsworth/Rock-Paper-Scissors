#pragma once

#include "AtlasData.h"
#include "DataManager.h"

class LoadAtlasData : public LoadData
{
public:
	explicit LoadAtlasData(const std::string path)
		: LoadData(path)
	{}
	AtlasCollection load() const;
	const char * image_source() const;
};
