#pragma once

#include "OptionsData.h"

class LoadOptionsData
{
	const char * path_;
public:
	LoadOptionsData(const char * path)
		: path_(path)
	{}
	~LoadOptionsData() {}
	OptionsCollection load() const;
};