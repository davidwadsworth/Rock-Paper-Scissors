#pragma once

#include "OptionsData.h"
#include "LoadData.h"

/**
 * @author David Wadsworth
 */

class LoadOptionsData : public LoadData
{
	OptionsCollection options_collection_;
public:
	explicit LoadOptionsData(const char * path) 
		: LoadData(path)
	{}
	OptionsCollection load();
};
