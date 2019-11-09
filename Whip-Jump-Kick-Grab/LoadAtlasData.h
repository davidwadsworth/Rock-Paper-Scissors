#pragma once

#include "AtlasData.h"

/**
 * @author David Wadsworth
 */

class LoadAtlasData : public LoadData
{
	AtlasCollection atlas_collection_;
public:
	explicit LoadAtlasData(const std::string path)
		: LoadData(path)
	{}

	AtlasCollection load();
	const char * image_source();
};
