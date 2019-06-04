#pragma once

#include <string>
#include <vector>

struct AudioData
{
	std::string path;
	int encoding;
};

struct AudioCollection : DataCollection
{
	std::vector<AudioData> data;
};