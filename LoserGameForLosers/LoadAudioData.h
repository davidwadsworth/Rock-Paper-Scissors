#pragma once
#include "AudioData.h"

class LoadAudioData
{
	const char * path_;
public:
	LoadAudioData(const char * path)
		: path_(path)
	{}
	~LoadAudioData() = default;
	AudioCollection load() const;
};
