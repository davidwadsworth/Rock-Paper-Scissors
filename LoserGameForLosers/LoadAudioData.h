#pragma once
#include "AudioData.h"

class LoadAudioData : public LoadData
{
public:
	LoadAudioData(const std::string path)
		: LoadData(path)
	{}
	AudioCollection load() const;
};
