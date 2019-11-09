#pragma once
#include "ControllerData.h"
#include "LoadData.h"

/**
 * @author David Wadsworth
 */

class LoadControllerData : public LoadData
{
	ControllerCollection controller_collection_;
public:
	explicit LoadControllerData(const std::string path)
		: LoadData(path)
	{}

	ControllerCollection load();
};
