#pragma once

#include <string>
#include <vector>

/**
 * @author David Wadsworth
 */

struct AudioData
{
	std::string path;
	int encoding = NULL;
};

struct AudioCollection : DataCollection
{
	std::vector<AudioData> data{};
};