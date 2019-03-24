#pragma once

#include <string>
#include <vector>

struct AudioData
{
	std::string path;
	int encoding;
};

struct AudioCollection
{
	std::string id;
	std::vector<AudioData> data;
};