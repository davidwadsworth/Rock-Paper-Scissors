#pragma once

#include <string>
#include <vector>

struct AudioData
{
	std::string path;
	std::string id;
	int encoding;
};

struct AudioCollection
{
	std::string id;
	std::vector<AudioData> data;
};