#pragma once
#include "ControllerData.h"
#include "DataManager.h"


class LoadControllerData : public LoadData
{
public:
	explicit LoadControllerData(const std::string path)
		: LoadData(path)
	{}

	ControllerCollection load() const;
};
