#pragma once
#include "AudioData.h"

/**
 * @author David Wadsworth
 */

class LoadAudioData : public LoadData
{
	AudioCollection audio_collection_;
public:
	explicit LoadAudioData(const std::string path)
		: LoadData(path)
	{}
	AudioCollection load();
};
