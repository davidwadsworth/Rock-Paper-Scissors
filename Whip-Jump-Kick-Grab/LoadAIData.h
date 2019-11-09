#pragma once

#include "AIData.h"
#include "LoadData.h"

/**
 * @author David Wadsworth
 */

class LoadAIData : public LoadData
{
	AICollection ai_collection_;
public:
	explicit LoadAIData(const std::string path)
		: LoadData(path)
	{}

	AICollection load();
};
