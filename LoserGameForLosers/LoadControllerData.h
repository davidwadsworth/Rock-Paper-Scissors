#pragma once
#include "ControllerData.h"

class LoadControllerData
{
	const char * path_;
public:
	explicit LoadControllerData(const char * path)
		: path_(path)
	{}
	~LoadControllerData() {}
	ControllerCollection load() const;
};
