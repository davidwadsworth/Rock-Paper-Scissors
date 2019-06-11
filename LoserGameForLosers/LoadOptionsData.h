#pragma once

#include "OptionsData.h"

class LoadOptionsData : public LoadData
{
public:
	LoadOptionsData(const char * path) 
		: LoadData(path)
	{}
	OptionsCollection load() const;
};
